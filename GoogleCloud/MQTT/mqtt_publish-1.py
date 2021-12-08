#!/usr/bin/env python3

import paho.mqtt.client as mqtt
import time

def main_fn():
   msg = "OFF"
   broker_address = "127.0.0.1"
   mqtt_username = "raman"
   mqtt_password = "Test@2021"
   client = mqtt.Client("CLIENT1")
   client.username_pw_set(mqtt_username, mqtt_password) # Sets the username and password
   print("connecting to broker")
   client.connect(broker_address) #connect to broker
   print("Publishing message to topic", "RELAY")
   client.publish("RELAY", msg)
   time.sleep(4) # wait

if __name__ == '__main__':
  main_fn()

