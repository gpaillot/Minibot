/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Guish
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
//#include "MyMCP2515.h"
//#include "MyMotor.h"
#include "MyDE0Nano.h"
#include "misc.h"
#include "SendMessage.h"


#define MYARM_RESETPIN = 19

using namespace std;

int main(int argc, char** argv) {
  
	MyDE0Nano *nano = new MyDE0Nano();
	nano->reset();
        time_sleep(1);
        gpioInitialise();
        
        unsigned int id;
        unsigned int length;
        unsigned int instr;
        unsigned int P0;
        unsigned int P1;
        unsigned int P2;
        unsigned char buf[4] = {0x00, 0x00, 0x00, 0x00};
        
        id = 0xfe;
        length = 0x05;
        instr = 0x03;
        P0 = 0x06;
        P1 = 0x00;
        P2 = 0x00;
        
        // SendMessage(id,length,instr,P0,P1,P2,MyDE0Nano *nano,unsigned char buf[4]);
        SendMessage(0xfe,0x05,0x03,0x06,0x00,0x00,nano,buf);
        cout << "CW angle limit set to 0" << endl;
        
        SendMessage(0xfe,0x05,0x03,0x08,0x00,0x00,nano,buf);
        cout << "CCW angle limit set to 0" << endl;
        
        SendMessage(0xfe,0x05,0x03,0x20,0xff,0x00,nano,buf);
        cout << "goal speed " << endl;
    
        nano->reset();
        /*allumage LED par spi
        unsigned char buf[4] = {0xd6, 0x03, 0x04, 0x08};
	nano->readWriteReg(WRITE, 0x00, buf, 4);
	
	genBuf(buf, 0x00, 0x00, 0x01, 0x19);
	nano->readWriteReg(WRITE, 0x01, buf, 4);
        cout << "Allumage LED" << endl;
	nano->reset();

	time_sleep(1);
        /*
        
        /* test SPI 4+5 = 9 cfr hw8 Legat
	unsigned char buf[4] = {0x00, 0x4F, 0x00, 0x00};
	nano->readWriteReg(WRITE, 0x00, buf, 4);
        
	genBuf(buf, 0x00, 0x00, 0x00, 0x05);
	nano->readWriteReg(WRITE, 0x01, buf, 4);
	
	genBuf(buf, 0x00, 0x00, 0x00, 0x04);
	nano->readWriteReg(WRITE, 0x02, buf, 4);

	nano->reset();

	time_sleep(1);
	
	genBuf(buf, 0x00, 0x00, 0x00, 0x00);
	nano->readWriteReg(READ, 0x03, buf, 4);
        
        //print reponse
	cout << (int) buf[0] << " " << (int) buf[1] << " " 
		 << (int) buf[2] << " " << (int) buf[3] << endl;	
        */
	delete nano;
    return 0;
}
