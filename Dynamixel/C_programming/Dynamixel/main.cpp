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
	
	
//	Rotate(0x08, 0x090, 0x00, nano, buf);
//	time_sleep(0.1);
//	Rotate(0x06, 0x090, 0x00, nano, buf);
//	time_sleep(0.1);
	Rotate(0xfe, 0x530, 0x00, nano, buf);
	time_sleep(5);
	FreeRun(0x08, nano, buf);
	LedOn(0x08,nano, buf);

	
	
	
	
	nano->reset();
	time_sleep(1);
	delete nano;
    return 0;
}


