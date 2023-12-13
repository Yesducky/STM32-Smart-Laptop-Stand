import serial
from pixeldata_2_jpg import *
import time
from face import *

def open_serial():
    port = 'com5'
    baudrate = 115200
    try:
        global ser
        ser = serial.Serial(port,baudrate,timeout=2)
        ser.flushInput()
        ser.flushOutput()
        if ser.isOpen():
            print("Connection success")
    except Exception as e:
        print("Error bruh: ",e)

def send_msg(pixel_data):
    print("sending messages")
    # height = 23
    ser.write(str(pixel_data).encode('ascii'))

def read_msg():
    try:
        print("Reading messages")
        pixel_data = b''
        while True:
            data = ser.read(ser.in_waiting)
            if b'Stop' in data:
                pixel_data += data
                return pixel_data
            elif data != b'':
                pixel_data += data
    except Exception as e:
        print("Error bruh: ",e)


            