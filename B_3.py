import paho.mqtt.client as mqtt
import time
import pandas as pd
import json

# Callback when the client connects to the MQTT broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker\n")
    else:
        print("Connection failed with code {rc}")

# Create an MQTT client instance
client = mqtt.Client("PythonPub_ass1_B_2")    

# Set the callback function
client.on_connect = on_connect

broker_address = "test.mosquitto.org"  # broker's address
broker_port = 1883
keepalive = 5
qos = 2

# Connect to the MQTT broker
client.connect(broker_address, broker_port, keepalive)

# Publish a message
try:
    file_path = r"PartB.xlsx"
    # Read the file
    df = pd.read_excel(file_path)

    # Convert the dataframe to JSON
    json_str = df.to_json(orient='records')
    json_obj = json.loads(json_str)

    client.loop_start()
    for row in json_obj:
        # Publish the message
        publish_topic = row['Location']
        client.publish(publish_topic, json.dumps(row), qos)
        # Wait for a moment to simulate some client activity
        time.sleep(1)

except KeyboardInterrupt:
    # Disconnect from the MQTT broker
    pass

client.loop_stop()
client.disconnect()
print("Disconnected from the MQTT broker")

