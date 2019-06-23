#for logs
import paho.mqtt.client as mqtt

def on_message(client, userdata, message):
    print(message.payload)

class Listener(object):

    def __init__(self, ip):
        self.l_client = mqtt.Client()

        self.l_client.connect(host=ip, port=1355)

        topic = 'control'
        self.l_client.on_message = on_message
        self.l_client.subscribe(topic) #, qos=0)

if __name__ == "__main__":
    sub = Listener('127.0.0.1')

sub.l_client.loop_forever()