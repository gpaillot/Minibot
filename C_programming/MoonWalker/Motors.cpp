/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Motors.cpp
 * Author: matthieu
 *
 * Created on March 6, 2017, 4:42 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <wiringPiSPI.h>
#include <pigpio.h>
#include <bitset>
#include <ctime>
#include <math/h>
#include <sys/time.h>

#include "MyMCP2515.h"
#include "MyDE0Nano.h"
#include "tourelle.h"
#include "globals.h"
#define PI 3.141592653

/*buld of the motor. address corresponds to the one of the CAN's PCB (ex: Minibot = 0x708)*/
MyMotors::MyTMotors(MyMCP2515 *myCan, MyDE0Nano *nano, int address, int motor)
{
    this_can = myCan;
    this_nano = nano;
    this_address = address;
    this_motor = motor; // 1 for the right motor, 2 for the left motor
    
}
MyTourelle::~MyTourelle() //sait pas du tout a quoi ca sert...
{
    
}

/*set the brake if activate is true, release them is it is false*/
void MyMotors::setBrake(bool activate) {
    if(activate)
    {
        makeData(data,GPLAT+offset,mask_brake,mask_brake,0x00,true);
        this_can->doSendMsg(this_address,data,3,0x00);
    }
    else
    {
        makeData(data,GPLAT+offset,mask_brake,0x00,0x00,true);
        this_can->doSendMsg(this_address,data,3,0x00);
    }
}

/*turn on the led if activate is true, off if false */
void MyMotors::setLed(bool activate){
    
    if(activate)
    {
        makeData(data,GPLAT+offset,mask_led,mask_led,0x00,true);
        this_can->doSendMsg(this_address,data,3,0x00);
    }
    else
    {
        makeData(data,GPLAT+offset,mask_led,0x00,0x00,true);
        this_can->doSendMsg(this_address,data,3,0x00);
    }
}

/*set the speed of the tourelle (positive: CCW, negative:CW)*/
void MyMotors::setSpeed(int speed){
    
    makeData(data,GPLAT+offset, mask_brake,0x00,0x00,true);// release brake
    this_can->doSendMsg(this_address,data,3,0x00);
    time_sleep(0.01);
    
    makeData(data,T1CON+offset, 0xb3,0x80,0x00,true);//T1CON
   this_can->doSendMsg(this_address,data, 3,0x00); 
    time_sleep(0.01);
    
    makeData(data,PR1+offset, 0xff, 0xff,0x00,true);//PR1
    this_can->doSendMsg(this_address,data, 3,0x00);
    time_sleep(0.01);
    
    makeData(data,PWM1+offset, 0xff,duty_zero + speed,0x00,true);//PWM1 set to speed
    this_can->doSendMsg(this_address,data, 3,0x00);
    time_sleep(0.01);
}

}

