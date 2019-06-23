#for logs
import paho.mqtt.client as mqtt
import json
import time

class Talker(object):

    def __init__(self, ip):
        self.t_client = mqtt.Client()
        self.t_client.connect(host=ip, port=1355)

    def send_data(self, speed, dir):
        topic = 'control'
        data = {"spd": speed, "dir": dir}

        self.t_client.publish(topic, json.dumps(data), qos=0)


if __name__ == "__main__":
    pub = Talker('127.0.0.1')
    # Continue the network loop, exit when an error occurs
    rc = 0
    while rc == 0:
        pub.send_data(50, -50)
        time.sleep(1)
rc = pub.t_client.loop()