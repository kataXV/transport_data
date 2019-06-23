#for teleops
import paho.mqtt.client as mqtt
import json
import time
import curses

def type_teleop(stdscr):
    # do not wait for input when calling getch
    stdscr.nodelay(1)
    while rc == 0:
        # get keyboard input, returns -1 if none available
        c = stdscr.getch()
        if c != -1:
            # print numeric value
            stdscr.addstr(str(c) + ' ')
            stdscr.refresh()
            # return curser to start position
            stdscr.move(0, 0)
            pub.send_data(c)

class Talker(object):

    def __init__(self, ip):
        self.t_client = mqtt.Client()
        self.t_client.connect(host=ip, port=1355)

    def send_data(self, dir):
        topic = 'teleops'
        data = {"dir": dir}

        self.t_client.publish(topic, json.dumps(data), qos=0)


if __name__ == "__main__":
    pub = Talker('127.0.0.1')
    rc = 0
    curses.wrapper(type_teleop)
    
    # Continue the network loop, exit when an error occurs
rc = pub.t_client.loop()