#for teleops
import paho.mqtt.client as mqtt
import json 

CONST_W = 119
CONST_A = 97
CONST_S = 115
CONST_D = 100
CONST_UP = 259
CONST_DOWN = 258
CONST_LEFT = 260
CONST_RIGHT = 261

def on_message(client, userdata, message):
    teleop_comands = json.loads(message.payload)
    print(teleop_comands['dir'])
    dir = teleop_comands['dir']
    if dir == CONST_W or dir == CONST_UP:
    	print("UP!!")
    if dir == CONST_S or dir == CONST_DOWN:
    	print("DOWN!!")
    if dir == CONST_A or dir == CONST_LEFT:
    	print("LEFT!!")
    if dir == CONST_D or dir == CONST_RIGHT:
    	print("RIGHT!!")

class Listener(object):

    def __init__(self, ip):
        self.l_client = mqtt.Client()

        self.l_client.connect(host=ip, port=1355)

        topic = 'teleops'
        self.l_client.on_message = on_message
        self.l_client.subscribe(topic) #, qos=0)

if __name__ == "__main__":
    sub = Listener('127.0.0.1')

sub.l_client.loop_forever()