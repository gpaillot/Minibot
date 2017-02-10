import MyTools.MyMCP2515
import MyTools.MyLCD
import time
from subprocess import check_output

import RPi.GPIO as GPIO
from time import sleep
import spidev
from math import*

# -*- coding: utf-8 -*-
def ShowString(str1,str2):
    MyLCD=MyTools.MyLCD.I2C_LCD()
    MyLCD.writeString(str1)
    MyLCD.setPosition(2,0)
    MyLCD.writeString(str2)
    
def initRoues():
    MyChip.DoSendMsg(0x708,[0x1E, 0x70,0x00], 3,MyChip.MCP2515_TX_STD_FRAME) # brake
    sleep(0.01)
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
    
def gauche(phi, vitesse):
	if (vitesse<10 and vitesse > 0):
		vitesse = 10
	elif(vitesse >-10 and vitesse < 0):
		vitesse = -10
	vitesse = int(vitesse)
	MyChip.DoSendMsg(0x708,[0x25, 0xff,128-vitesse], 3,MyChip.MCP2515_TX_STD_FRAME) # PWM1 (right)
	sleep(0.01)
	MyChip.DoSendMsg(0x708,[0x26, 0xff,128+vitesse], 3,MyChip.MCP2515_TX_STD_FRAME) # PWM2 (left)
	sleep(0.01)
	print("gauche    ", phi)
	
	
def droite(phi, vitesse):
	if (vitesse<10 and vitesse > 0):
		vitesse = 10
	elif(vitesse >-10 and vitesse < 0):
		vitesse = -10
	vitesse = int(vitesse)
	MyChip.DoSendMsg(0x708,[0x25, 0xff,128+vitesse], 3,MyChip.MCP2515_TX_STD_FRAME) # PWM1 (right)
	sleep(0.01)
	MyChip.DoSendMsg(0x708,[0x26, 0xff,128-vitesse], 3,MyChip.MCP2515_TX_STD_FRAME) # PWM2 (left)
	sleep(0.01)
	print("droite    ", phi)
	
def stop(phi):
	MyChip.DoSendMsg(0x708,[0x25, 0xff,128], 3,MyChip.MCP2515_TX_STD_FRAME) # PWM1 (right)
	sleep(0.01)
	MyChip.DoSendMsg(0x708,[0x26, 0xff,128], 3,MyChip.MCP2515_TX_STD_FRAME) # PWM2 (left)
	sleep(0.01)
	print("stop    ", phi)
	
def avance(vitesse):
    MyChip.DoSendMsg(0x708,[0x25, 0xff,128+vitesse], 3,MyChip.MCP2515_TX_STD_FRAME) # PWM1 (right)
    sleep(0.01)
    MyChip.DoSendMsg(0x708,[0x26, 0xff,128+vitesse], 3,MyChip.MCP2515_TX_STD_FRAME) # PWM2 (left)
    sleep(0.01)
    print("avance")


MyChip=MyTools.MyMCP2515.MCP2515()
MyChip.DoInit
MyARM_ResetPin = 19 # Pin 4 of connector = BCM19 = GPIO[1]

MySPI_FPGA = spidev.SpiDev()
MySPI_FPGA.open(0,0)
MySPI_FPGA.max_speed_hz = 500000

GPIO.setmode(GPIO.BCM)


GPIO.setwarnings(False)
GPIO.setup(MyARM_ResetPin, GPIO.OUT)

GPIO.output(MyARM_ResetPin, GPIO.HIGH)
sleep(0.1)
GPIO.output(MyARM_ResetPin, GPIO.LOW)
sleep(0.1)


# BCM= numérotation électronique de la puce ( juste un type de numérotation )

ShowString("Matthieu est un", "petit coquin")



#init tourelle
MyChip.DoSendMsg(0x508,[0x1E, 0x10,0x00], 3,MyChip.MCP2515_TX_STD_FRAME) # brake
sleep(0.01)
MyChip.DoSendMsg(0x508,[0x21, 0xb3,0x80], 3,MyChip.MCP2515_TX_STD_FRAME) # T1CON
sleep(0.01)
MyChip.DoSendMsg(0x508,[0x23, 0xff, 0xff], 3, MyChip.MCP2515_TX_STD_FRAME) # PR1
sleep(0.01)
command = 25+128 #25+128 COMMANDE DE VITESSE
MyChip.DoSendMsg(0x508,[0x25, 0xff,command], 3,MyChip.MCP2515_TX_STD_FRAME)
initRoues();
myDutyCycle = 128
error_add = 0
counter_add = 1
stop_angle = 0
while 1==1: 
    ToSPI = [0x03, 0x00, 0x00, 0x00, 0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    #print(FromSPI)
    Counter = pow(256,3)*FromSPI[1] + pow(256,2)*FromSPI[2] + 256*FromSPI[3] + FromSPI[4]
    
    ToSPI = [0x05, 0x00, 0x00, 0x00, 0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    posBeacon = pow(256,3)*FromSPI[1] + pow(256,2)*FromSPI[2] + 256*FromSPI[3] + FromSPI[4]
    
    ToSPI = [0x06, 0x00, 0x00, 0x00, 0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    negBeacon = pow(256,3)*FromSPI[1] + pow(256,2)*FromSPI[2] + 256*FromSPI[3] + FromSPI[4]
    

    ToSPI = [0x07, 0x00, 0x00, 0x00, 0x00]
    FromSPI = MySPI_FPGA.xfer2(ToSPI)
    #print(FromSPI)
    nTikz = pow(256,3)*FromSPI[1] + pow(256,2)*FromSPI[2] + 256*FromSPI[3] + FromSPI[4]
    
    if(nTikz==0):
        nTikz=1
        
    moyenne_beacon = float((negBeacon + posBeacon)/2)
    largeur_beacon = float((negBeacon - posBeacon)/2)
    
    alpha_demi = float(largeur_beacon*360/nTikz)
    phi = float(moyenne_beacon*360/nTikz)
    
    
    if (alpha_demi==0):
        alpha_demi = 0.01;
    if(alpha_demi==180):
        alpha_demi = 180.01;
		
    distance = float(4.0/(sin(radians(alpha_demi*1.5))))
    if (distance<0):
        distance = 1000 
    #vitesseRot = 0.2*phi_prime
    vitesseAv = 15
    phi_prime = phi -135
    vitesseRot = 0.20*phi_prime
    if(phi_prime>5 and stop_angle==0):
        gauche(phi_prime, vitesseRot)
    elif(phi_prime<-5 and stop_angle==0):
        droite(phi_prime, vitesseRot)
    else:
        stop_angle=1
        if (phi-135>20 or  phi-135<-20):
             stop_angle = 0

        if(distance>40):
            if (distance>400):
                distance = 30 
            speed_ref = 25*26*(distance-30)
            ToSPI_1 = [0x01, 0x4F, 0x00, 0x00, 0x00]
            GetData_ans = MySPI_FPGA.xfer2(ToSPI_1)
            string = bin(GetData_ans[1])
            sng = string[0:3]
            print(sng)
            Counter_prev = -2*(int(sng,0))*pow(2,31)+ pow(256,3)*GetData_ans[1] + pow(256,2)*GetData_ans[2] + 256*GetData_ans[3] + GetData_ans[4]
            #Counter_prev = pow(256,3)*FromSPI[1] + pow(256,2)*FromSPI[2] + pow(256,1)*FromSPI[3] + FromSPI[4]
            sleep(0.01)
            #ToSPI_1 = [0x01, 0x4F, 0x00, 0x00, 0x00]
            GetData_ans = MySPI_FPGA.xfer2(ToSPI_1)
            string = bin(GetData_ans[1])
            sng = string[0:3]
            print(sng)
            Counter_curr = -2*(int(sng,0))*pow(2,31)+ pow(256,3)*GetData_ans[1] + pow(256,2)*GetData_ans[2] + 256*GetData_ans[3] + GetData_ans[4]
            #FromSPI = MySPI_FPGA.xfer2(ToSPI_1)
            #Counter_curr = pow(256,3)*FromSPI[1] + pow(256,2)*FromSPI[2] + pow(256,1)*FromSPI[3] +FromSPI[4]	
            Delta = Counter_curr - Counter_prev
            speed = Delta/0.01
            Kp = 0.00004
            Ki = 0.0005
            error_prev = error_add
            error_add = speed_ref -speed
            myDutyCycle = int(myDutyCycle + (Kp*error_add)+Ki*error_add -Kp*error_prev)
            if (myDutyCycle >=160):
                myDutyCycle = 160
            elif (myDutyCycle <=50):
                myDutyCycle =50
            print(distance, myDutyCycle)
            MyChip.DoSendMsg(0x708,[0x25, 0xff,myDutyCycle], 3,MyChip.MCP2515_TX_STD_FRAME) # PWM1 (right)
            MyChip.DoSendMsg(0x708,[0x26, 0xff,myDutyCycle], 3,MyChip.MCP2515_TX_STD_FRAME) # PWM2 (left)
        else:
            stop(phi)
            
            
       
    #print(str(Counter),  str(Tikz_balise), str(nTikz), str(phi))
    

    
    
