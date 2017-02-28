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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    roue();
    
    printf("Before init\n");
    initTourelle();
    printf("After init\n");
    time_sleep(10);
    //stop();
    
    return 0;
}

