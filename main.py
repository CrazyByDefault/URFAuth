import serial
import sys

route = '/dev/ttyUSB2'
s = serial.Serial(route,9600)


def read_key():
    i=0
    while(i<1000):
        print(1)
        k = s.readline()
       # if k.splitlines() == [' 47 C8 12 2B ']:
        #    return 1
        print(k)
        if(k):
            return k
           #break;

def ask_key():
    s.write('key')

def authenticate():
    s.flush()
    ask_key()
    key_recv = read_key().splitlines() 
    print key_recv
    if key_recv == [' 47 C8 12 2B ']:
        sys.exit(0)
    #code = read_key()
    #if code!=1:
    #    sys.exit(0)
    else:
        print ("Authentication failed. Received ")
        sys.exit(-1)


authenticate()
sys.exit(-1)
