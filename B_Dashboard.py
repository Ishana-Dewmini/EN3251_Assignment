import pandas as pd
import json
import paho.mqtt.client as mqtt
import time

# Callback when the client connects to the MQTT broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker\n")
    else:
        print("Connection failed with code {rc}")
        
# Provide the path to your Excel file
excel_file = 'PartB.xlsx'

# Create an MQTT client instance
client = mqtt.Client("Pub1")      

# Set the callback function
client.on_connect = on_connect

broker_address = "test.mosquitto.org"  # broker's address
broker_port = 1883
keepalive = 5
qos = 2
publish_topic = "Group07/partB/4"

# Connect to the MQTT broker
client.connect(broker_address, broker_port, keepalive)


# Start the MQTT loop to handle network traffic
client.loop_start()

# Publish loop
try:
        while True:
            # Read the Excel file into a DataFrame
            dictionary = {}

            df = pd.read_excel(excel_file)
            json_str = df.to_json(orient='records')
            json_obj = json.loads(json_str)

            for i in range(len(json_obj)):
                dictionary[str(i)] = json_obj[i]

            data_out=json.dumps(dictionary) #encode object to JSON
            
            client.publish(publish_topic,data_out,qos)
            print(f"Published message '{data_out}' to topic '{publish_topic}'\n")

            time.sleep(5)

except KeyboardInterrupt:
    # Disconnect from the MQTT broker
    pass

client.loop_stop()
client.disconnect()
print("Disconnected from the MQTT broker")
