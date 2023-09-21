import paho.mqtt.client as mqtt
import time
import json

# Callback when the client connects to the MQTT broker
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT broker\n")
    else:
        print("Connection failed with code {rc}")


# Create an MQTT client instance
client = mqtt.Client("PythonPub")

# Set the callback function
client.on_connect = on_connect

broker_address = "test.mosquitto.org"  # broker's address
broker_port = 1883
keepalive = 5
qos = 0
publish_topic = "Phoenix"

# Connect to the MQTT broker
client.connect(broker_address, broker_port, keepalive)

# Start the MQTT loop to handle network traffic
#client.loop_start()

# Publish loop
#read_file_name = ".Xlsx"
value = "main/PartB.xlsx"#input('Enter the file name: ')

read_file_name = value # read_file_name
file = open(read_file_name, 'r')
print(file.read())

# try:
    
#     while True:
#         # Publish a message to the send topic after reading the file
#         read_file_name = value + read_file_name
        
#         with open(read_file_name) as json_file:
#             file = json.load(json_file)

#         data_out=json.dumps(file) #encode object to JSON
#         client.publish(publish_topic,data_out,qos)
#         print(f"Published message '{data_out}' to topic '{publish_topic}'\n")
        
        # Wait for a moment to simulate some client activity
        #time.sleep(6)

#except KeyboardInterrupt:
    # Disconnect from the MQTT broker
 #   pass
#client.loop_stop()
#client.disconnect()
print("Disconnected from the MQTT broker")
