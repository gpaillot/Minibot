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
#include <iomanip>
using namespace std;

// SendMessage(id,length,instr,P0,P1,P2,MyDE0Nano *nano,unsigned char buf[4]);

void SendMessage(unsigned int id,unsigned int length,unsigned int instr,unsigned int P0,unsigned int P1,unsigned int P2,MyDE0Nano *nano, unsigned char buf[4])
{
    int check = (~(id+length+instr+P0+P1+P2)) & 0x000000FF;
	
    genBuf(buf,check, instr, length, id);
    nano->readWriteReg(WRITE, 0x00, buf, 4);
    genBuf(buf, 0x00, P2, P1, P0);
    nano->readWriteReg(WRITE, 0x01, buf, 4);
    time_sleep(0.8);
}

void LedOn(unsigned int id, MyDE0Nano *nano, unsigned char buf[4])
{
	/*
	 LedOn(0x08, nano, buf); --> turns the LED of dynamixel with id 0x08 ON
	 */
	SendMessage(id,0x04,0x03,0x19,0x01,0x00,nano,buf);
	cout << "Dynamixel 0x0" << id << " : " << "led ON " << endl;
	
}

void LedOff(unsigned int id, MyDE0Nano *nano, unsigned char buf[4])
{
	/*
	 LedOFF(0x08, nano, buf); --> turns the LED of dynamixel with id 0x08 OFF
	 */
	SendMessage(id,0x04,0x03,0x19,0x00,0x00,nano,buf);
	cout << "Dynamixel 0x0" << id << " : " << "led OFF " << endl;
}

void EndlessTurn(unsigned int id, int speed, MyDE0Nano *nano, unsigned char buf[4])
{
	/*
	 speed must be set to a value between 0x00 and 0x3FF
	 EndlessTurn(0x08, 0x3ff, nano, buf); --> sets the max speed to dynamixel with id 0x08
	 */
	int speedL = speed & 0x000000FF;
	int speedH = (speed & 0x00000F00)>>8;
	double percent = 100*speed/1023.0;
	
	SendMessage(id,0x05,0x03,0x06,0x00,0x00,nano,buf);
	//cout << "CW angle limit set to 0" << endl;
	SendMessage(id,0x05,0x03,0x08,0x00,0x00,nano,buf);
	//cout << "CCW angle limit set to 0" << endl;
    
	SendMessage(id,0x05,0x03,0x20,speedL,speedH,nano,buf); // set speed 
	printf("Dynamixel 0x%02x : endless turn at speed: 0x%03x (= %d/1023 = %.2f%% of max speed)\n", id, speed, speed, percent);
	printf("Dynamixel 0x%02x : speedH = 0x%02x and speedL = 0x%02x \n\n", id, speedH, speedL);
	
	//cout << "Dynamixel 0x0" << id << " : " << "endless turn at speed: 0x" << hex << speed << "( = " << dec << speed << "/1023 = " << c << ")" << endl;
	//cout << "Dynamixel 0x0" << id << " : speedH = 0x0" << hex << speedH << " and speedL = 0x" << hex << speedL << endl;
	
}

void Rotate(unsigned int id, int speed, int position, MyDE0Nano *nano, unsigned char buf[4])
{
	SendMessage(id,0x05,0x03,0x06,0x00,0x00,nano,buf); // 0x000 --> CW angle limit set to 30
	SendMessage(id,0x05,0x03,0x08,0xff,0x03,nano,buf); // 0x3ff --> CCW angle limit set to 300
	int speedL = speed & 0x000000FF;
	int speedH = (speed & 0x00000F00)>>8;
	double percent = 100*speed/1023.0;
	int positionL = position & 0x000000FF;
	int positionH = (position & 0x00000F00)>>8;
	double angle = 30+position/1023.0*300;
	SendMessage(id,0x05,0x03,0x20,speedL,speedH,nano,buf); // set speed
	SendMessage(id,0x05,0x03,0x1E,positionL,positionH,nano,buf); // set position
	printf("Dynamixel 0x%02x : rotation at speed: 0x%03x (= %d/1023 = %.2f%% of max speed)\n", id, speed, speed, percent);
	printf("Dynamixel 0x%02x : speedH = 0x%02x and speedL = 0x%02x \n", id, speedH, speedL);
	printf("Dynamixel 0x%02x : going to position: 0x%03x (= %.2f degrees) \n", id, position, angle);
	printf("Dynamixel 0x%02x : positionH = 0x%02x and positionL = 0x%02x \n\n", id, positionH, positionL);
	
}