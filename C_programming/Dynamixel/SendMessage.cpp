/*
 * Send message to the dynamixel using spi
 * 
 * Group 1, 2017.
 */


#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <pigpio.h>
#include <ctime>
#include <sys/time.h>
#include "MyDE0Nano.h"
#include "misc.h"
#include "SendMessage.h"

void SendMessage(unsigned int id,unsigned int length,unsigned int instr,unsigned int P0,unsigned int P1,unsigned int P2,MyDE0Nano *nano, unsigned char buf[4])
{
    int check = (~(id+length+instr+P0+P1+P2)) & 0x000000FF;
    
    genBuf(buf,check, instr, length, id);
    nano->readWriteReg(WRITE, 0x00, buf, 4);
    genBuf(buf, 0x00, P2, P1, P0);
    nano->readWriteReg(WRITE, 0x01, buf, 4);
    time_sleep(1);
}

