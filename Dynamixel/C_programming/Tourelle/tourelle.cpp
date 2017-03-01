/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <wiringPiSPI.h>
#include <pigpio.h>
#include <bitset>
#include <ctime>
#include <sys/time.h>

#include "MyMCP2515.h"
#include "MyDE0Nano.h"
#include "tourelle.h"
#include "globals.h"


/*buld of the tourelle. address corresponds to the one of the CAN's PCB (ex: Minibot = 0x508)*/
MyTourelle::MyTourelle(MyMCP2515 *myCan, MyDE0Nano *nano, int address)
{
    this_can = myCan;
    this_nano = nano;
    this_address = address;
    
}
MyTourelle::~MyTourelle() //sait pas du tout a quoi ca sert...
{
    
}

/*set the brake if activate is true, release them is it is false*/
void MyTourelle::setBrake(bool activate) {
    if(activate)
    {
        makeData(data,GPLAT+offset,mask_brake,mask_brake);
        this_can->doSendMsg(this_address,data,3,0x00);
    }
    else
    {
        makeData(data,GPLAT+offset,mask_brake,0x00);
        this_can->doSendMsg(this_address,data,3,0x00);
    }
}

/*turn on the led if activate is true, off if false */
void MyTourelle::setLed(bool activate){
    
    if(activate)
    {
        makeData(data,GPLAT+offset,mask_led,mask_led);
        this_can->doSendMsg(this_address,data,3,0x00);
    }
    else
    {
        makeData(data,GPLAT+offset,mask_led,0x00);
        this_can->doSendMsg(this_address,data,3,0x00);
    }
}

/*set the speed of the tourelle (positive: CCW, negative:CW)*/
void MyTourelle::setSpeed(int speed){
    
    makeData(data,GPLAT+offset, mask_brake,0x00);// release brake
    this_can->doSendMsg(this_address,data,3,0x00);
    time_sleep(0.01);
    
    makeData(data,T1CON+offset, 0xb3,0x80);//T1CON 
   this_can->doSendMsg(this_address,data, 3,0x00); 
    time_sleep(0.01);
    
    makeData(data,PR1+offset, 0xff, 0xff);//PR1
    this_can->doSendMsg(this_address,data, 3,0x00);
    time_sleep(0.01);
    
    makeData(data,PWM1+offset, 0xff,duty_zero + speed);//PWM1 set to speed
    this_can->doSendMsg(this_address,data, 3,0x00);
    time_sleep(0.01);
}