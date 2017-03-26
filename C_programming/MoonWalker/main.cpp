/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: GuiP
 *
 * Created on 28 février 2017, 23:35
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
//#include "MyMCP2515.h"
//#include "MyMotor.h"

#include "initTourelle.h"
#include "stop.h"
#include "globals.h"
#include "tourelle.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
   
    MyMCP2515 *MyCAN = new MyMCP2515();
    MyCAN->doInit();
    MyDE0Nano *nano = new MyDE0Nano();
    
    MyTourelle tourelle(MyCAN, nano, 0x508);
    MyMotors motors(MyCAN, nano, 0x708);
    
    nano->reset();
    
    motors.setLed(true);
    /*tourelle.setLed(false);
    tourelle.setSpeed(-25);
    time_sleep(5);
    tourelle.setBrake(true);*/
    
    return 0;
}

