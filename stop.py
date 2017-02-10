import MyTools.MyMCP2515
import MyTools.MyLCD
import time
from subprocess import check_output
from tkinter import*
import RPi.GPIO as GPIO
from time import sleep
import spidev
# -*- coding: utf-8 -*-

MyChip=MyTools.MyMCP2515.MCP2515()
MyChip.DoInit
MyARM_ResetPin = 19 # Pin 4 of connector = BCM19 = GPIO[1]

MySPI_FPGA = spidev.SpiDev()
MySPI_FPGA.open(0,0)
MySPI_FPGA.max_speed_hz = 500000

GPIO.setmode(GPIO.BCM)

# BCM= numérotation électronique de la puce ( juste un type de numérotation )


GPIO.setwarnings(False)
GPIO.setup(MyARM_ResetPin, GPIO.OUT)

GPIO.output(MyARM_ResetPin, GPIO.HIGH)
sleep(0.1)
GPIO.output(MyARM_ResetPin, GPIO.LOW)
sleep(0.1)

#brake roues + tourelle
MyChip.DoSendMsg(0x508,[0x1E, 0x10,0x10], 3,MyChip.MCP2515_TX_STD_FRAME) # brake
sleep(0.01)
MyChip.DoSendMsg(0x708,[0x1E, 0x70,0x00], 3,MyChip.MCP2515_TX_STD_FRAME) # brake
sleep(0.01)
#roues
MyChip.DoSendMsg(0x708,[0x1E, 0x40,0x40], 3,MyChip.MCP2515_TX_STD_FRAME) # led
sleep(0.01)
MyChip.DoSendMsg(0x708,[0x21, 0xb3,0x80], 3,MyChip.MCP2515_TX_STD_FRAME) # T1CON (roue de gauche quand on lit bien l'écran) 
sleep(0.01)
MyChip.DoSendMsg(0x708,[0x22, 0xb3, 0x80], 3, MyChip.MCP2515_TX_STD_FRAME) # T2CON (roue de droite quand on lit bien l'écran)
sleep(0.01)
MyChip.DoSendMsg(0x708,[0x23, 0xff, 0xff], 3, MyChip.MCP2515_TX_STD_FRAME) # PR1
sleep(0.01)
MyChip.DoSendMsg(0x708,[0x24, 0xff, 0xff], 3, MyChip.MCP2515_TX_STD_FRAME) # PR2
sleep(0.01)
MyChip.DoSendMsg(0x708,[0x25, 0xff,0x80], 3,MyChip.MCP2515_TX_STD_FRAME) # reset PWM1 left
sleep(0.01)
MyChip.DoSendMsg(0x708,[0x26, 0xff,0x80], 3,MyChip.MCP2515_TX_STD_FRAME) # reset PWM1 left
sleep(0.01)
#MyChip.DoSendMsg(0x708,[0x1E, 0x70,0x70], 3,MyChip.MCP2515_TX_STD_FRAME) # brake

#tourelle

MyChip.DoSendMsg(0x508,[0x21, 0xb3,0x80], 3,MyChip.MCP2515_TX_STD_FRAME) # T1CON
sleep(0.01)
MyChip.DoSendMsg(0x508,[0x23, 0xff, 0xff], 3, MyChip.MCP2515_TX_STD_FRAME) # PR1
sleep(0.01)
command = 0+128
MyChip.DoSendMsg(0x508,[0x25, 0xff,command], 3,MyChip.MCP2515_TX_STD_FRAME)


