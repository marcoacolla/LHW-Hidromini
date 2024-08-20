import paho.mqtt.client as mqtt
import requests
import time

url = "http://10.0.0.181:3000/api/sensors"

interval = 0.5

lastMessageTime = time.time()
isPaused = False


measures = {  
    "pressure1": {"value": 0.0, "type": float, "id": "00"},
    "pressure2": {"value": 0.0, "type": float, "id": "01"},
    "pressure3": {"value": 0.0, "type": float, "id": "02"},

    "motor_rpm": {"value": 0.0, "type": float, "id": "03"},
    "gen_rpm": {"value": 0.0, "type": float, "id": "04"},

    "dc_cur": {"value": 0.0, "type": float, "id": "05"},
    "dc_volt": {"value": 0.0, "type": float, "id": "06"},

    "valve1": {"value": False, "type": bool, "id": "07"},
    "valve2": {"value": False, "type": bool, "id": "08"}
}



def updateSite(data):
    response = requests.post(url, json=data)
    print("Status Code:", response.status_code)
    print("Resposta:", response.json())

def prepare_data(measures):
    to_send = {}
    for key, sub_dict in measures.items():
        to_send[key] = {"value": sub_dict["value"]}
    return to_send

toSend = prepare_data(measures)

def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code.is_failure:
        print(f"Failed to connect: {reason_code}. loop_forever() will retry connection")
    else:
    # Subscribing in on_connect() means that if we lose the connection and
        for topic, info in measures.items():
            client.subscribe(f"/mcc/{topic}")


def on_message(client, userdata, message):
    global lastMessageTime,isPaused, toSend
    lastMessageTime = time.time()
    isPaused = False
    print("Received message '" + str(message.payload) + "' on topic '" + message.topic)
    for topic, infos in measures.items():
        if message.topic == f"/mcc/{topic}":
            infos["value"] = infos["type"](message.payload)
    toSend = prepare_data(measures)

    


print('MQTT to InfluxDB bridge')
mqtt_client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message

mqtt_client.connect("10.0.1.119",1883,60)
# C_onnect to the MQTT server and process messages in a background thread. 
mqtt_client.loop_start()

print("Suguei")

while True:
    if (time.time() - lastMessageTime) > interval and isPaused == False:
        
        updateSite(toSend)
        print("Suga")


        isPaused = True
    else:
        print("Suguei")
    time.sleep(0.1)