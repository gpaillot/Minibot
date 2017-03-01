/* 
 * File:   main.cpp
 * Author: Group1
 *
 * Created on 2 décembre 2016, 03:09AM
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
#include "MyDE0Nano.h"
#include "misc.h"
#include "Functions.h"
//#include "MyMCP2515.h"
//#include "MyMotor.h"



#define MYARM_RESETPIN = 19
using namespace std;

int main(int argc, char** argv) {
	
	MyDE0Nano *nano = new MyDE0Nano(); // instantiate 
	nano->reset();
	time_sleep(1);
	gpioInitialise();
	unsigned char buf[4] = {0x00, 0x00, 0x00, 0x00}; // first instantiation
	
	
	Rotate(0x08, 0x300, 0x00, nano, buf);
	time_sleep(2);
	EndlessTurn(0x08, 0x328, nano, buf);
	time_sleep(5);
	Rotate(0x08, 0x300, 0x1ff, nano, buf);
	time_sleep(1);
	EndlessTurn(0x08, 0x128, nano, buf);
	Rotate(0x08, 0x300, 0x065, nano, buf);
	time_sleep(0.5);
	Rotate(0x08, 0x300, 0x3e0, nano, buf);
	time_sleep(2);
	Rotate(0x08, 0x300, 0x00, nano, buf);
	EndlessTurn(0x08, 0x128, nano, buf);
	EndlessTurn(0x08, 0x00, nano, buf);
	LedOn(0x08, nano, buf); 

	
	nano->reset();
	time_sleep(1);
	delete nano;
    return 0;
}