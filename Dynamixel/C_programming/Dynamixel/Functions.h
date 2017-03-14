/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Functions.h
 * Author: Euroclear
 *
 * Created on February 28, 2017, 6:43 PM
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H


void SendMessage(unsigned int id,unsigned int length,unsigned int instr,unsigned int P0,unsigned int P1,unsigned int P2,MyDE0Nano *nano,unsigned char buf[4]);
void LedOn(unsigned int id, MyDE0Nano *nano, unsigned char buf[4]);
void LedOff(unsigned int id, MyDE0Nano *nano, unsigned char buf[4]);
void EndlessTurn(unsigned int id, int speed, MyDE0Nano *nano, unsigned char buf[4]);
void Rotate(unsigned int id, int speed, int position, MyDE0Nano *nano, unsigned char buf[4]);

#endif /* FUNCTIONS_H */
