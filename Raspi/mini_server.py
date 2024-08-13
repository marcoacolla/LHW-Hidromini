import paho.mqtt.client as mqtt
import requests

url = "http://10.0.0.181:3000/api/variables"

data = {
    "pressure1": 0,
    "pressure2": 0,
    "pressure3": 0,

    "motor_rpm": 0,
    "gen_rpm": 0,

    "dc_cur": 0
}

def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code.is_failure:
        print(f"Failed to connect: {reason_code}. loop_forever() will retry connection")
    else:
    # Subscribing in on_connect() means that if we lose the connection and
        for topic, info in data.items():
            client.subscribe(f"/mcc/{topic}")


def on_message(client, userdata, message):
    print("Received message '" + str(message.payload) + "' on topic '" + message.topic)
    for topic, value in data.items():
        if message.topic == f"/mcc/{topic}":
            data[topic] = float(message.payload)
    response = requests.post(url, json=data)
    print("Status Code:", response.status_code)
    print("Resposta:", response.json())


print('MQTT to InfluxDB bridge')
mqtt_client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message

mqtt_client.connect("10.0.1.119",1883,60)
# C_onnect to the MQTT server and process messages in a background thread. 
mqtt_client.loop_forever()