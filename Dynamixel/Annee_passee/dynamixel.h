/* Author: Fish
 Description: Header for the dynamixels functions
 Date: 15/05/2015
 */
#ifndef DYNAMIXEL_H_
#define DYNAMIXEL_H_
#include "CtrlStruct.h"
//Dynamixels constants:
#define DATA_8 1
#define DATA_16 2

#define CLOSED 1
#define OPEN 0

#define IN 0
#define OUT 1

#define UP 0
#define DOWN 1

#define DYN_LED 0x19
#define DYN_CW 0x06
#define DYN_CCW 0x08
#define DYN_POSITION 0x1e
#define DYN_SPEED 0x20
#define DYN_ID 0x03
#define DYN_BAUD 0x04

#define DYN_CURRENT 0x44
#define DYN_MOVING 0x2e

#define DYN_CURRENT_POSITION 0x24
#define DYN_CURRENT_SPEED 0x26

#define DYN_GOAL_TORQUE 0x47
#define DYN_GOAL_TORQUE_ENABLE 0x46

#define DYN_ID_ALL 0xfe
#define DYN_ID_SUNSHADE 0x1
#define DYN_ID_GRIPPER_1 0x08
#define DYN_ID_GRIPPER_2 0x09
#define DYN_ID_FISH_1 0x00
#define DYN_ID_FISH_2 0x03


#define POSITION 0 
#define SPEED 1 

#define DYN_MAXIMUM_TORQUE 256
#define DYN_CALIBRATION_TORQUE 0x05
//Functions
void init_dynamixels(CtrlStruct *cvs);
void sortirBac(CtrlStruct *cvs);
void downMagnets(CtrlStruct *cvs);
void upMagnets(CtrlStruct *cvs);
void fishIn(CtrlStruct *cvs);
void fishUp(CtrlStruct *cvs);
void fish(CtrlStruct *cvs);
void rentrerBac(CtrlStruct *cvs);
void dynSendMessage(int ID,int data_size,int address,int value);
int dynReadRegister(int ID,int data_size,int address,int try);
void dynPosGo(CtrlStruct *cvs,int index, int id);
void dynCycleGo(CtrlStruct *cvs,int index,int id);
void dynSwitchMode(CtrlStruct *cvs,int id);
void dynSwitch(CtrlStruct *cvs,int id);
int map_id_index_dynamixels(int id);
void serrerPince(CtrlStruct *cvs);
void lacherPince(CtrlStruct *cvs);
void raiseSunshade(CtrlStruct *cvs);
void takeFloor1(CtrlStruct *cvs);
void atFloor1(CtrlStruct *cvs);
void takeFloor0(CtrlStruct *cvs);
void takeFloor2(CtrlStruct *cvs);
void pumpFloor3(CtrlStruct *cvs);
void pumpFloor4(CtrlStruct *cvs);
void releaseBlocks(CtrlStruct *cvs);
void rentrerPince(CtrlStruct *cvs);

#endif