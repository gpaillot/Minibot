from subprocess import check_output
import time
from time import sleep
import MyTools.MyLCD
# -*- coding: utf-8 -*-
import RPi.GPIO as GPIO
from time import sleep
import spidev
from math import*

MyARM_ResetPin = 19 # Pin 4 of connector = BCM19 = GPIO[1]

MySPI_FPGA = spidev.SpiDev()
MySPI_FPGA.open(0,0)
MySPI_FPGA.max_speed_hz = 500000

GPIO.setmode(GPIO.BCM)

# BCM = numérotation électronique de la puce ( juste un type de numérotation )


GPIO.setwarnings(False)
GPIO.setup(MyARM_ResetPin, GPIO.OUT)

GPIO.output(MyARM_ResetPin, GPIO.HIGH)
sleep(0.1)
GPIO.output(MyARM_ResetPin, GPIO.LOW)
sleep(0.1)

#allumage led
ToSPI = [0x80, 0xd6, 0x03, 0x04, 0x08]
FromSPI = MySPI_FPGA.xfer2(ToSPI)

ToSPI = [0x81, 0x00, 0x00, 0x01, 0x19]
FromSPI = MySPI_FPGA.xfer2(ToSPI)
print("Allumage led")
#sleep(10)
    
"""
#lire ID
ToSPI = [0x80, 0xee, 0x02, 0x04, 0x08]
FromSPI = MySPI_FPGA.xfer2(ToSPI)
 
ToSPI = [0x81, 0x00, 0x00, 0x00, 0x03]
FromSPI = MySPI_FPGA.xfer2(ToSPI)
#print("Allumage led")

sleep(0.1)

ToSPI = [0x81, 0x00, 0x00, 0x00, 0x02]#from PI to DE0
FromSPI = MySPI_FPGA.xfer2(ToSPI)



GPIO.output(MyARM_ResetPin, GPIO.HIGH)
sleep(0.1)
GPIO.output(MyARM_ResetPin, GPIO.LOW)
sleep(0.1)


ToSPI = [0x00, 0x00, 0x00, 0x00, 0x00]#from DE0 to PI
FromSPI = MySPI_FPGA.xfer2(ToSPI)
print(FromSPI)

ToSPI = [0x01, 0x00, 0x00, 0x00, 0x00]
FromSPI = MySPI_FPGA.xfer2(ToSPI)
print(FromSPI)

ToSPI = [0x02, 0x00, 0x00, 0x00, 0x00]
FromSPI = MySPI_FPGA.xfer2(ToSPI)
print(FromSPI)

ToSPI = [0x03, 0x00, 0x00, 0x00, 0x00]
FromSPI = MySPI_FPGA.xfer2(ToSPI)
print(FromSPI)
"""

GPIO.output(MyARM_ResetPin, GPIO.HIGH)
sleep(0.1)
GPIO.output(MyARM_ResetPin, GPIO.LOW)
sleep(0.1)

while 1==1:
    """
	#set ID->8
    ToSPI = [0x80, 0xef, 0x03, 0x04, 0xfe]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    
    ToSPI = [0x81, 0x00, 0x00, 0x08, 0x03]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    print("ID")
    
    sleep(1)
    #allumage led
    ToSPI = [0x80, 0xd6, 0x03, 0x04, 0x08]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    
    ToSPI = [0x81, 0x00, 0x00, 0x01, 0x19]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    print("Allumage led")
    
    sleep(1)

    #led off
    ToSPI = [0x80, 0xe1, 0x03, 0x04, 0xfe]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

    ToSPI = [0x81, 0x00, 0x00, 0x00, 0x19]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    print("Eteignage led")
    sleep(1)
    
    
    
    #torque 50%
    ToSPI = [0x80, 0xeb, 0x03, 0x05, 0xfe]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

    ToSPI = [0x81, 0x00, 0x01, 0xff, 0x0e]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    print("torque 50%")
    
    sleep(0.1)
    
    #angle 300
    ToSPI = [0x80, 0xd9, 0x03, 0x05, 0xfe]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

    ToSPI = [0x81, 0x00, 0x03, 0xff, 0x1e]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    print("Angle 300")
    
    sleep(15)
    
     #angle 0
    ToSPI = [0x80, 0xdb, 0x03, 0x05, 0xfe]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

    ToSPI = [0x81, 0x00, 0x00, 0x00, 0x1e]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    print("Angle 0")
    
    sleep(10)
    
    
    
    #vitesse
    ToSPI = [0x80, 0xd7, 0x03, 0x05, 0xfe]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

    ToSPI = [0x81, 0x00, 0x02, 0x00, 0x20]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    print("vitesse")
    
    sleep(0.1)
    
   
    
def check(ID, length, instr, P0, P1, P2):
	inter = ID+length+instr+P0+P1+P2
	if(inter > 256):
		inter = inter - 256
	
    """
    sleep(0.1)
    print("CW angle limit set to 0")
    ToSPI = [0x80, 0xf3, 0x03, 0x05, 0xfe]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

    ToSPI = [0x81, 0x00, 0x00, 0x00, 0x06]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    
    sleep(0.1)
    print("CCW angle limit set to 0")
    ToSPI = [0x80, 0xf1, 0x03, 0x05, 0xfe]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

    ToSPI = [0x81, 0x00, 0x00, 0x00, 0x08]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    
    sleep(0.1)
    print("goal speed set to 0x1ff")
    ToSPI = [0x80, 0xd9, 0x03, 0x05, 0xfe]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)

    ToSPI = [0x81, 0x00, 0x01, 0xff, 0x20]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    
	
