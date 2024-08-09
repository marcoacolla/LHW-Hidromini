import paho.mqtt.client as mqtt

def on_connect(client, userdata, mid, reason_code_list, properties):
    if reason_code_list[0].is_failure:
        print(f"Broker rejected you subscription: {reason_code_list[0]}")
    else:
        print(f"Broker granted the following QoS: {reason_code_list[0].value}")

    # Subscribing in on_connect() means that if we lose the connection and
    client.subscribe("/esp8266/temperature")
    client.subscribe("/esp8266/humidity")

def on_message(client, userdata, message):
    print("Received message '" + str(message.payload) + "' on topic '" + message.topic)
    

print('MQTT to InfluxDB bridge')
mqtt_client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message

mqtt_client.connect("127.0.0.1")
# C_onnect to the MQTT server and process messages in a background thread. 
mqtt_client.loop_forever()


