import paho.mqtt.client as mqtt
import requests

url = "http://10.0.0.181:3000/api/variables"

measures = {  
    "pressure1": {"value": 0.0, "type": float},
    "pressure2": {"value": 0.0, "type": float},
    "pressure3": {"value": 0.0, "type": float},

    "motor_rpm": {"value": 0.0, "type": float},
    "gen_rpm": {"value": 0.0, "type": float},

    "dc_cur": {"value": 0.0, "type": float},
    "dc_volt": {"value": 0.0, "type": float},

    "valve1": {"value": False, "type": bool},
}


def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code.is_failure:
        print(f"Failed to connect: {reason_code}. loop_forever() will retry connection")
    else:
    # Subscribing in on_connect() means that if we lose the connection and
        for topic, info in measures.items():
            client.subscribe(f"/mcc/{topic}")


def on_message(client, userdata, message):
    print("Received message '" + str(message.payload) + "' on topic '" + message.topic)
    for topic, infos in measures.items():
        if message.topic == f"/mcc/{topic}":
            infos["value"] = infos["type"](message.payload)
    response = requests.post(url, json=measures)
    print("Status Code:", response.status_code)
    print("Resposta:", response.json())


print('MQTT to InfluxDB bridge')
mqtt_client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message

mqtt_client.connect("10.0.1.119",1883,60)
# C_onnect to the MQTT server and process messages in a background thread. 
mqtt_client.loop_forever()