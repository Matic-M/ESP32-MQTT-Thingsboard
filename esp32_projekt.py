import paho.mqtt.client as mqtt
import time

server = "broker.hivemq.com"
server2 = "demo.thingsboard.io"
port = 1883
username = "2s5sLPcl5etymniu7XXD"
password = ""

BASE_TOPIC = "ONTKS"
TOPIC = "Projekt_Matic_Mubi"

def on_connect(client, userdata, flags, rc):
    client.subscribe(f"{BASE_TOPIC}/{TOPIC}")
    if rc == 0:
        print("Connected to source broker with result code: " + str(rc))
    else:
        print("Connection to source broker refused!")

def on_publish(client, userdata, mid):
    print("Message was sent successfully to destination broker!")

def on_message(client, userdata, message):
    print(f"Received message on {message.topic} topic: {message.payload.decode('utf-8')}")
    client_destination.publish(f"{BASE_TOPIC}/{TOPIC}", message.payload)
   
# client for connecting to hivemq
client_source = mqtt.Client()
client_source.on_connect = on_connect
client_source.on_message = on_message
client_source.connect(server, port)  # Connect to the source broker
client_source.loop_start()  # Start the loop to handle incoming messages

# client for connecting to thingsboard
client_destination = mqtt.Client()
client_destination.on_publish = on_publish
client_destination.username_pw_set(username, password)
client_destination.connect(server2, port)  # Connect to the destination broker
   
while True:
    time.sleep(5)  # loop
