/* Author: Fish
 Description: All fonctions use to communicate with dynamixels
 Date: 15/05/2015
 */
# define dynamixel
#include "dynamixel.h"
#include "MyCyclone.h"
char theStr[128];
void init_dynamixels(CtrlStruct *cvs){

    cvs->dynamixels->isACtive[0] = 1;
    cvs->dynamixels->isACtive[1] = 1;
    cvs->dynamixels->isACtive[2] = 1;
    cvs->dynamixels->isACtive[3] = 1;
    cvs->dynamixels->isACtive[4] = 1;
    
    cvs->dynamixels->dynamixelMode[0] = POSITION;
    cvs->dynamixels->dynamixelMode[1] = POSITION;
    cvs->dynamixels->dynamixelMode[2] = POSITION;
    cvs->dynamixels->dynamixelMode[3] = POSITION;
    cvs->dynamixels->dynamixelMode[4] = POSITION;

    cvs->dynamixels->dynamixelSpeedWheel[0] = 10;
    cvs->dynamixels->dynamixelSpeedWheel[1] = 10;
    cvs->dynamixels->dynamixelSpeedWheel[2] = 10;
    cvs->dynamixels->dynamixelSpeedWheel[3] = 500;
    cvs->dynamixels->dynamixelSpeedWheel[4] = 350;
    
    cvs->dynamixels->dynamixelSpeedJoin[0] = 0;
    cvs->dynamixels->dynamixelSpeedJoin[1] = 100;
    cvs->dynamixels->dynamixelSpeedJoin[2] = 100;
    cvs->dynamixels->dynamixelSpeedJoin[3] = 300;
    cvs->dynamixels->dynamixelSpeedJoin[4] = 100;
    
    /*If a value in the range of 0~1023 is used, it is stopped by setting to 0 while rotating to CCW direction.
    If a value in the range of 1024~2047 is used, it is stopped by setting to 1024 while rotating to CW direction.
    */

    cvs->dynamixels->dynamixelPos1[0][0] = 400;
    cvs->dynamixels->dynamixelPos1[1][0] = 650;
    cvs->dynamixels->dynamixelPos1[2][0] = 3650;
    cvs->dynamixels->dynamixelPos1[3][0] = 10;
    cvs->dynamixels->dynamixelPos1[4][0] = 870;
    
    cvs->dynamixels->dynamixelPos2[0][0] = 400;
    cvs->dynamixels->dynamixelPos2[1][0] = 1200;
    cvs->dynamixels->dynamixelPos2[2][0] = 2750;
    cvs->dynamixels->dynamixelPos2[3][0] = 800;
    cvs->dynamixels->dynamixelPos2[4][0] = 1100;
    
    cvs->dynamixels->dynamixelPos3[0][0] = 400;
    cvs->dynamixels->dynamixelPos3[1][0] = 1400;
    cvs->dynamixels->dynamixelPos3[2][0] = 10;
    cvs->dynamixels->dynamixelPos3[3][0] = 800;
    cvs->dynamixels->dynamixelPos3[4][0] = 1000;
    
    cvs->dynamixels->dynamixelPos4[0][0] = 400;
    cvs->dynamixels->dynamixelPos4[1][0] = 2600;
    cvs->dynamixels->dynamixelPos4[2][0] = 1600;
    cvs->dynamixels->dynamixelPos4[3][0] = 800;
    cvs->dynamixels->dynamixelPos4[4][0] = 300;
    
    cvs->dynamixels->dynamixelPos5[0][0] = 400;
    cvs->dynamixels->dynamixelPos5[1][0] = 2600;
    cvs->dynamixels->dynamixelPos5[2][0] = 1050;
    cvs->dynamixels->dynamixelPos5[3][0] = 800;
    cvs->dynamixels->dynamixelPos5[4][0] = 300;
    
    cvs->dynamixels->dynamixelPos1[0][1] = 0;
    cvs->dynamixels->dynamixelPos1[1][1] = 0;
    cvs->dynamixels->dynamixelPos1[2][1] = 1;
    cvs->dynamixels->dynamixelPos1[3][1] = 3;
    cvs->dynamixels->dynamixelPos1[4][1] = 0;
    
    cvs->dynamixels->dynamixelPos2[0][1] = 0;
    cvs->dynamixels->dynamixelPos2[1][1] = 0;
    cvs->dynamixels->dynamixelPos2[2][1] = 1;
    cvs->dynamixels->dynamixelPos2[3][1] = 2;
    cvs->dynamixels->dynamixelPos2[4][1] = 0;
   
    cvs->dynamixels->dynamixelPos3[0][1] = 0;
    cvs->dynamixels->dynamixelPos3[1][1] = 0;
    cvs->dynamixels->dynamixelPos3[2][1] = 1;
    cvs->dynamixels->dynamixelPos3[3][1] = 1;
    cvs->dynamixels->dynamixelPos3[4][1] = 0;
    
    cvs->dynamixels->dynamixelPos4[0][1] = 0;
    cvs->dynamixels->dynamixelPos4[1][1] = 0;
    cvs->dynamixels->dynamixelPos4[2][1] = 1;
    cvs->dynamixels->dynamixelPos4[3][1] = 1;
    cvs->dynamixels->dynamixelPos4[4][1] = 0;
    
    cvs->dynamixels->dynamixelPos5[0][1] = 0;
    cvs->dynamixels->dynamixelPos5[1][1] = 0;
    cvs->dynamixels->dynamixelPos5[2][1] = 2;
    cvs->dynamixels->dynamixelPos5[3][1] = 1;
    cvs->dynamixels->dynamixelPos5[4][1] = 0;
    
    /*0 to 1023 (0x3FF) is available.  The unit is 0.29 degree.
    */

    cvs->dynamixels->dynamixelStart[0] = 0;
    cvs->dynamixels->dynamixelStart[1] = 0;
    cvs->dynamixels->dynamixelStart[2] = 0;
    cvs->dynamixels->dynamixelStart[3] = 0;
    cvs->dynamixels->dynamixelStart[4] = 0;
    
    dynSendMessage(DYN_ID_ALL, DATA_8 , DYN_LED , 0);
    dynSendMessage(DYN_ID_ALL, DATA_8 , DYN_LED , 1);
    dynSendMessage(DYN_ID_ALL, DATA_8 , DYN_LED , 0);
    
    if(cvs->dynamixels->isACtive[1])dynSendMessage(DYN_ID_GRIPPER_1, DATA_16 , 0x0e , DYN_MAXIMUM_TORQUE);
    if(cvs->dynamixels->isACtive[2])dynSendMessage(DYN_ID_GRIPPER_2, DATA_16 , 0x0e , DYN_MAXIMUM_TORQUE);
    if(cvs->dynamixels->isACtive[3])dynSendMessage(DYN_ID_FISH_1, DATA_16 , 0x0e , 700);
    if(cvs->dynamixels->isACtive[4])dynSendMessage(DYN_ID_FISH_2, DATA_16 , 0x0e ,700);
    if(cvs->dynamixels->isACtive[0])dynSendMessage(DYN_ID_SUNSHADE, DATA_16 , DYN_LED-1 , (0x1<<8)+0x1);
    if(cvs->dynamixels->isACtive[1])dynSendMessage(DYN_ID_GRIPPER_1, DATA_16 , DYN_LED-1 , (0x1<<8)+0x1);
    if(cvs->dynamixels->isACtive[2])dynSendMessage(DYN_ID_GRIPPER_2, DATA_16 , DYN_LED-1 , (0x1<<8)+0x1);
    if(cvs->dynamixels->isACtive[3])dynSendMessage(DYN_ID_FISH_1, DATA_16 , DYN_LED-1 , (0x1<<8)+0x1);
    if(cvs->dynamixels->isACtive[4])dynSendMessage(DYN_ID_FISH_2, DATA_16 , DYN_LED-1 , (0x1<<8)+0x1);
    if(cvs->dynamixels->isACtive[1])dynSendMessage(DYN_ID_GRIPPER_1,DATA_16,DYN_CCW,0x0FFF);
    if(cvs->dynamixels->isACtive[2])dynSendMessage(DYN_ID_GRIPPER_2,DATA_16,DYN_CCW,0x0FFF);
    if(cvs->dynamixels->isACtive[3])dynSendMessage(DYN_ID_FISH_1,DATA_16,DYN_CCW,0x00);
    if(cvs->dynamixels->isACtive[4])dynSendMessage(DYN_ID_FISH_2,DATA_16,DYN_CCW,0x00);
    if(cvs->dynamixels->isACtive[0])dynSendMessage(DYN_ID_SUNSHADE,DATA_16,DYN_CW,450);
    if(cvs->dynamixels->isACtive[0])dynSendMessage(DYN_ID_SUNSHADE,DATA_16,DYN_CCW,790);
    
    if(cvs->dynamixels->isACtive[0])dynSendMessage(DYN_ID_SUNSHADE,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedJoin[0]);
    if(cvs->dynamixels->isACtive[1])dynSendMessage(DYN_ID_GRIPPER_1,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedJoin[1]);
    if(cvs->dynamixels->isACtive[2])dynSendMessage(DYN_ID_GRIPPER_2,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedJoin[2]);

    if(cvs->dynamixels->isACtive[3])dynSendMessage(DYN_ID_FISH_1,DATA_16,DYN_SPEED,0);
    if(cvs->dynamixels->isACtive[4])dynSendMessage(DYN_ID_FISH_2,DATA_16,DYN_SPEED,0);
    dynSendMessage(DYN_ID_ALL, DATA_8 , DYN_GOAL_TORQUE_ENABLE , 0x0);
    if(cvs->dynamixels->isACtive[1])dynPosGo(cvs,3,DYN_ID_GRIPPER_1);
    if(cvs->dynamixels->isACtive[2])dynSendMessage(DYN_ID_GRIPPER_2, DATA_16 , DYN_GOAL_TORQUE , DYN_CALIBRATION_TORQUE);
    if(cvs->dynamixels->isACtive[2])dynSendMessage(DYN_ID_GRIPPER_2, DATA_8 , DYN_GOAL_TORQUE_ENABLE , 0x1);
    if(cvs->dynamixels->isACtive[2]){
        int mySpeed = 100;
        int myCurrent = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT,3);
        while((mySpeed > 0) ||(myCurrent != 2048 + DYN_CALIBRATION_TORQUE)){
            mySpeed = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT_SPEED,3);
            myCurrent = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT,3);
        }
    
    
        dynSendMessage(DYN_ID_GRIPPER_2, DATA_8 , DYN_GOAL_TORQUE_ENABLE , 0x0);
        cvs->dynamixels->dynamixelPos1[2][0] = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT_POSITION,4);
        dynPosGo(cvs,5,DYN_ID_GRIPPER_1);
    }
    cvs->dynamixels->cycle[0] = 0;
    cvs->dynamixels->cycle[1] = 0;
    if(cvs->dynamixels->dynamixelPos1[2][0] > 2000){
        cvs->dynamixels->cycle[2] = 1;
        cvs->dynamixels->dynamixelPos1[2][1] =1;
    }else{
        cvs->dynamixels->cycle[2] = 0;
        cvs->dynamixels->dynamixelPos1[2][1] =0;
    }
   cvs->dynamixels->dynamixelPos1[3][0] = dynReadRegister(DYN_ID_FISH_1,DATA_16,DYN_CURRENT_POSITION,4);

    cvs->dynamixels->cycle[3] =0;
    cvs->dynamixels->cycle[4] = 0;

    
    cvs->dynamixels->gripper_state = OPEN;
    cvs->dynamixels->bac_state = IN;
    cvs->dynamixels->magnets_state = UP;
    cvs->dynamixels->Need_recalibrate = 0;
    
    cvs->dynamixels->securite = 1;

    
}
int map_id_index_dynamixels(int id){
    int j;
    switch(id){
        case DYN_ID_SUNSHADE: j=0; break;
        case DYN_ID_GRIPPER_1: j=1; break;
        case DYN_ID_GRIPPER_2: j=2; break;
        case DYN_ID_FISH_1: j=3; break;
        case DYN_ID_FISH_2: j=4; break;
        default: j=0; break;
    }
    return j;
}
void dynPosGo(CtrlStruct *cvs,int index,int id){
    int j = map_id_index_dynamixels(id);
    if(cvs->dynamixels->isACtive[j] && ((cvs->inputs->t < TIME_END-1.5) || id == DYN_ID_SUNSHADE)){
        switch(index){
            case 1: if(cvs->dynamixels->cycle[j] == cvs->dynamixels->dynamixelPos1[j][1]){
                    dynSendMessage(id,DATA_16,DYN_POSITION,cvs->dynamixels->dynamixelPos1[j][0]);
                }else{
                    dynCycleGo(cvs,index,id);
                    dynPosGo(cvs,index,id);
                }break;
            case 2: if(cvs->dynamixels->cycle[j] == cvs->dynamixels->dynamixelPos2[j][1]){
                    dynSendMessage(id,DATA_16,DYN_POSITION,cvs->dynamixels->dynamixelPos2[j][0]);
                }else{
                    dynCycleGo(cvs,index,id);
                    dynPosGo(cvs,index,id);
                }break;
            case 3: if(cvs->dynamixels->cycle[j] == cvs->dynamixels->dynamixelPos3[j][1]){
                    dynSendMessage(id,DATA_16,DYN_POSITION,cvs->dynamixels->dynamixelPos3[j][0]);
                }else{
                    dynCycleGo(cvs,index,id);
                    dynPosGo(cvs,index,id);
                }break;
            case 4: if(cvs->dynamixels->cycle[j] == cvs->dynamixels->dynamixelPos4[j][1]){
                    dynSendMessage(id,DATA_16,DYN_POSITION,cvs->dynamixels->dynamixelPos4[j][0]);
                }else{
                    dynCycleGo(cvs,index,id);
                    dynPosGo(cvs,index,id);
                }break;
            case 5: if(cvs->dynamixels->cycle[j] == cvs->dynamixels->dynamixelPos5[j][1]){
                    dynSendMessage(id,DATA_16,DYN_POSITION,cvs->dynamixels->dynamixelPos5[j][0]);
                }else{
                    dynCycleGo(cvs,index,id);
                    dynPosGo(cvs,index,id);
                }break;
            default:break;
        }
        
        if(cvs->dynamixels->securite){
            cvs->states->time_start_wait = cvs->inputs->t;
            while(dynReadRegister(id,DATA_8,DYN_MOVING,3)){
                if(index == 4)MyDelayMs(100);
                refresh_inputs(cvs);
                if(cvs->inputs->t > TIME_END-0.5 && cvs->states->robot_state != AT_END){
                   cvs->states->step_action = 0;
                   cvs->states->robot_state = AT_END;
                   break;
                }
                if((cvs->inputs->t - cvs->states->time_start_wait) > 10.0 && cvs->states->robot_state != AT_END){
                   break;
                }
            }
        }
    }
}
void serrerPince(CtrlStruct *cvs){
    if(cvs->dynamixels->isACtive[1]){
        dynSendMessage(DYN_ID_GRIPPER_1, DATA_16 , DYN_GOAL_TORQUE , 0x78+1024);
        dynSendMessage(DYN_ID_GRIPPER_1, DATA_8 , DYN_GOAL_TORQUE_ENABLE , 0x1);
        int mySpeed = 100;
        int myCurrent = dynReadRegister(DYN_ID_GRIPPER_1,DATA_16,DYN_CURRENT,3);
        while((mySpeed > 0) ||(myCurrent != 2048 - 0x78)){
            mySpeed = dynReadRegister(DYN_ID_GRIPPER_1,DATA_16,DYN_CURRENT_SPEED,3);
            myCurrent = dynReadRegister(DYN_ID_GRIPPER_1,DATA_16,DYN_CURRENT,3);
        }
        cvs->dynamixels->gripper_state = CLOSED;
    }
}
void lacherPince(CtrlStruct *cvs){
    if(cvs->dynamixels->isACtive[1]){
        dynSendMessage(DYN_ID_GRIPPER_1, DATA_8 , DYN_GOAL_TORQUE_ENABLE , 0x0);
        cvs->dynamixels->gripper_state = OPEN;
    }
}
void rentrerPince(CtrlStruct *cvs){
    if(cvs->dynamixels->gripper_state == OPEN && cvs->dynamixels->isACtive[1] && cvs->dynamixels->isACtive[2]){
        dynSendMessage(DYN_ID_GRIPPER_1, DATA_8 , DYN_GOAL_TORQUE_ENABLE , 0x0);
        dynPosGo(cvs,3,DYN_ID_GRIPPER_1);
        dynPosGo(cvs,1,DYN_ID_GRIPPER_2);
        dynPosGo(cvs,4,DYN_ID_GRIPPER_1);
    }
}   
void raiseSunshade(CtrlStruct *cvs){
    dynPosGo(cvs,1,DYN_ID_SUNSHADE);
}
void pumpFloor3(CtrlStruct *cvs){
    if(cvs->dynamixels->gripper_state == OPEN){
        dynPosGo(cvs,3,DYN_ID_GRIPPER_1);
        dynPosGo(cvs,4,DYN_ID_GRIPPER_2);
    }
}
void pumpFloor4(CtrlStruct *cvs){
    if(cvs->dynamixels->gripper_state == OPEN){
        dynPosGo(cvs,3,DYN_ID_GRIPPER_1);
        dynPosGo(cvs,5,DYN_ID_GRIPPER_2);
    }
}
void releaseBlocks(CtrlStruct *cvs){
    if(cvs->dynamixels->gripper_state == CLOSED && cvs->dynamixels->isACtive[1] && cvs->dynamixels->isACtive[2]){
        dynSendMessage(DYN_ID_GRIPPER_2, DATA_16 , DYN_GOAL_TORQUE , 2);
        dynSendMessage(DYN_ID_GRIPPER_2, DATA_8 , DYN_GOAL_TORQUE_ENABLE , 0x1);
            //MyDelayMs(20000);//complete course
        int mySpeed = 100;
        int myCurrent = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT,3);
        while((mySpeed > 0) ||(myCurrent != 2048 + 2)){
            mySpeed = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT_SPEED,3);
            myCurrent = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT,3);
        }
        dynSendMessage(DYN_ID_GRIPPER_2, DATA_8 , DYN_GOAL_TORQUE_ENABLE , 0x0);
        lacherPince(cvs);
        dynPosGo(cvs,2,DYN_ID_GRIPPER_1);
        if(cvs->dynamixels->Need_recalibrate){
            dynSendMessage(DYN_ID_GRIPPER_2, DATA_16 , DYN_GOAL_TORQUE , DYN_CALIBRATION_TORQUE);
            dynSendMessage(DYN_ID_GRIPPER_2, DATA_8 , DYN_GOAL_TORQUE_ENABLE , 0x1);
            mySpeed = 100;
            myCurrent = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT,3);
            while((mySpeed > 0) ||(myCurrent != 2048 + DYN_CALIBRATION_TORQUE)){
                mySpeed = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT_SPEED,3);
                myCurrent = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT,3);
            }
            dynSendMessage(DYN_ID_GRIPPER_2, DATA_8 , DYN_GOAL_TORQUE_ENABLE , 0x0);
            cvs->dynamixels->dynamixelPos1[2][0] = dynReadRegister(DYN_ID_GRIPPER_2,DATA_16,DYN_CURRENT_POSITION,4);
            if(cvs->dynamixels->dynamixelPos1[2][0] > 2000){
                cvs->dynamixels->cycle[2] = 1;
                cvs->dynamixels->dynamixelPos1[2][1] =1;
            }else{
                cvs->dynamixels->cycle[2] = 0;
                cvs->dynamixels->dynamixelPos1[2][1] =0;
            }
            cvs->dynamixels->Need_recalibrate = 0;
        }
    }
}
void takeFloor0(CtrlStruct *cvs){
    if(cvs->dynamixels->gripper_state == OPEN && cvs->dynamixels->isACtive[1]){
        //dynPosGo(cvs,3,DYN_ID_GRIPPER_1);
        dynPosGo(cvs,1,DYN_ID_GRIPPER_2);
        serrerPince(cvs);
        //dynPosGo(cvs,2,DYN_ID_GRIPPER_2);
    }
}
void takeFloor1(CtrlStruct *cvs){
    if(cvs->dynamixels->gripper_state == OPEN && cvs->dynamixels->isACtive[1] && cvs->dynamixels->isACtive[2]){
        dynPosGo(cvs,3,DYN_ID_GRIPPER_1);
        dynPosGo(cvs,2,DYN_ID_GRIPPER_2);
        serrerPince(cvs);
        dynPosGo(cvs,3,DYN_ID_GRIPPER_2);
    }
}
void atFloor1(CtrlStruct *cvs){
    if(cvs->dynamixels->gripper_state == OPEN && cvs->dynamixels->isACtive[1] && cvs->dynamixels->isACtive[2]){
        dynPosGo(cvs,3,DYN_ID_GRIPPER_1);
        dynPosGo(cvs,2,DYN_ID_GRIPPER_2);
    }
}
void takeFloor2(CtrlStruct *cvs){
    if(cvs->dynamixels->gripper_state == OPEN && cvs->dynamixels->isACtive[1] && cvs->dynamixels->isACtive[2]){
        dynPosGo(cvs,3,DYN_ID_GRIPPER_1);
        dynPosGo(cvs,3,DYN_ID_GRIPPER_2);
        serrerPince(cvs);
        dynPosGo(cvs,5,DYN_ID_GRIPPER_2);
        cvs->dynamixels->Need_recalibrate = 1;
    }
}

void sortirBac(CtrlStruct *cvs){
    if((cvs->dynamixels->bac_state == IN) && cvs->dynamixels->isACtive[3]){
        dynSendMessage(DYN_ID_FISH_1,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedWheel[3]+1024);
        cvs->states->time_start_wait = cvs->inputs->t;
        while((cvs->inputs->t - cvs->states->time_start_wait) < 8.5){
            refresh_inputs(cvs);
           if(cvs->inputs->t > TIME_END)break;
        }
        dynSendMessage(DYN_ID_FISH_1,DATA_16,DYN_SPEED,0);
        cvs->dynamixels->bac_state = OUT;
    }
}
void downMagnets(CtrlStruct *cvs){
    if(cvs->dynamixels->magnets_state == UP && cvs->dynamixels->isACtive[4] && cvs->dynamixels->bac_state == OUT){
        dynSendMessage(DYN_ID_FISH_2,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedWheel[4]);
        cvs->states->time_start_wait = cvs->inputs->t;
        while((cvs->inputs->t - cvs->states->time_start_wait) < 1.8){
            refresh_inputs(cvs);
            if(cvs->inputs->t > TIME_END)break;
        }
        dynSendMessage(DYN_ID_FISH_2,DATA_16,DYN_SPEED,0);
        cvs->dynamixels->magnets_state = DOWN;
    }
}
void fishIn(CtrlStruct *cvs){
    rentrerBac(cvs);
    dynPosGo(cvs,2,DYN_ID_FISH_2);
}
void fishUp(CtrlStruct *cvs){
    upMagnets(cvs);
}
void fish(CtrlStruct *cvs){
    dynPosGo(cvs,1,DYN_ID_FISH_2);
    sortirBac(cvs);
    downMagnets(cvs);
}
void upMagnets(CtrlStruct *cvs){
    if(cvs->dynamixels->magnets_state == DOWN && cvs->dynamixels->isACtive[4]){
        dynSendMessage(DYN_ID_FISH_2, DATA_16 , 0x0e , 700);
        dynSendMessage(DYN_ID_FISH_2, DATA_16 , 0x22 ,700);
        dynSendMessage(DYN_ID_FISH_2,DATA_16,DYN_CCW,0x03FF);
        cvs->dynamixels->securite = 0;
        dynSendMessage(DYN_ID_FISH_2,DATA_16,DYN_POSITION,0x0);
        cvs->dynamixels->securite = 1;
    }
}
void rentrerBac(CtrlStruct *cvs){
    if(cvs->dynamixels->bac_state == OUT && cvs->dynamixels->isACtive[3] && cvs->dynamixels->magnets_state == UP){
        dynSendMessage(DYN_ID_FISH_1,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedWheel[3]);
        cvs->states->time_start_wait = cvs->inputs->t;
        while((cvs->inputs->t - cvs->states->time_start_wait) < 8){
            refresh_inputs(cvs);
            if(cvs->inputs->t > TIME_END)break;
        }
        dynSendMessage(DYN_ID_FISH_1,DATA_16,DYN_SPEED,0);
        cvs->dynamixels->bac_state = IN;
    }
}
void dynCycleGo(CtrlStruct *cvs,int index,int id){
    int j = map_id_index_dynamixels(id);
    int delta_cycle;
    switch(index){
        case 1: delta_cycle = cvs->dynamixels->cycle[j] - cvs->dynamixels->dynamixelPos1[j][1];  break;
        case 2: delta_cycle = cvs->dynamixels->cycle[j] - cvs->dynamixels->dynamixelPos2[j][1];  break;
        case 3: delta_cycle = cvs->dynamixels->cycle[j] - cvs->dynamixels->dynamixelPos3[j][1];  break;
        case 4: delta_cycle = cvs->dynamixels->cycle[j] - cvs->dynamixels->dynamixelPos4[j][1];  break;
        case 5: delta_cycle = cvs->dynamixels->cycle[j] - cvs->dynamixels->dynamixelPos5[j][1];  break;
        default:break;
    }
    int i,pos;
    for( i = 0; i < abs(delta_cycle); i++){
        if(delta_cycle > 0){
            if(id == DYN_ID_GRIPPER_1 ||id == DYN_ID_GRIPPER_2){
                dynSendMessage(id,DATA_16,DYN_POSITION,0xFFF);
                while(dynReadRegister(id,DATA_8,DYN_MOVING,3)){}
                dynSendMessage(id,DATA_16,DYN_CCW,0x00);
                dynSendMessage(id,DATA_16,DYN_SPEED,0);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedWheel[j]);
                int pos = 0xFFF;
                while(pos > 0xFF0){
                    pos = dynReadRegister(id,DATA_16,DYN_CURRENT_POSITION,4);
                }
                dynSendMessage(id,DATA_16,DYN_SPEED,0);
                dynSendMessage(id,DATA_16,DYN_CCW,0xFFF);
                dynSendMessage(id,DATA_16,DYN_POSITION,0);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedJoin[j]);
            }else if(id == DYN_ID_FISH_2){
                dynSendMessage(id,DATA_16,DYN_POSITION,0x3FF);
                while(dynReadRegister(id,DATA_8,DYN_MOVING,3)){}
                dynSendMessage(id,DATA_16,DYN_CCW,0x00);
                dynSendMessage(id,DATA_16,DYN_SPEED,0);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedWheel[j]);
                int pos = 0x3FF;
                while((pos < 100)||(pos >900)){
                    pos = dynReadRegister(id,DATA_16,DYN_CURRENT_POSITION,4);
                }
                dynSendMessage(id,DATA_16,DYN_SPEED,1);
                dynSendMessage(id,DATA_16,DYN_CCW,0x3FF);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedJoin[j]);
                dynSendMessage(id,DATA_16,DYN_POSITION,0);
            }else{
                dynSendMessage(id,DATA_16,DYN_POSITION,0x3FF);
                while(dynReadRegister(id,DATA_8,DYN_MOVING,3)){
                    MyDelayMs(100);
                }
                dynSendMessage(id,DATA_16,DYN_CCW,0x00);
                dynSendMessage(id,DATA_16,DYN_SPEED,0);
                MyDelayMs(100);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedWheel[j]);
                int pos = 0x3FF;
                while((pos >900)){
                    pos = dynReadRegister(id,DATA_16,DYN_CURRENT_POSITION,4);
                }
                dynSendMessage(id,DATA_16,DYN_SPEED,1);
                dynSendMessage(id,DATA_16,DYN_CCW,0x3FF);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedJoin[j]);
                dynSendMessage(id,DATA_16,DYN_POSITION,0);
            }
            
            cvs->dynamixels->cycle[j]--;
        }else{
            if(id == DYN_ID_GRIPPER_1 ||id == DYN_ID_GRIPPER_2){
                dynSendMessage(id,DATA_16,DYN_POSITION,0x0);
                while(dynReadRegister(id,DATA_8,DYN_MOVING,3)){}
                dynSendMessage(id,DATA_16,DYN_CCW,0x00);
                dynSendMessage(id,DATA_16,DYN_SPEED,0);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedWheel[j]+1024);
                int pos = 0x0;
                while(pos < 0x10){
                    pos = dynReadRegister(id,DATA_16,DYN_CURRENT_POSITION,4);
                }
                dynSendMessage(id,DATA_16,DYN_SPEED,0);
                dynSendMessage(id,DATA_16,DYN_CCW,0xFFF);
                dynSendMessage(id,DATA_16,DYN_POSITION,0xFFF);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedJoin[j]);
            }else if(id == DYN_ID_FISH_2){
                dynSendMessage(id,DATA_16,DYN_POSITION,0x0);
                while(dynReadRegister(id,DATA_8,DYN_MOVING,3)){}
                dynSendMessage(id,DATA_16,DYN_CCW,0x00);
                dynSendMessage(id,DATA_16,DYN_SPEED,0);
                dynSendMessage(id,DATA_16,DYN_SPEED,350+1024);
                int pos = 0x0;
                while((pos < 100)||(pos >900)){
                    pos = dynReadRegister(id,DATA_16,DYN_CURRENT_POSITION,4);
                }
                dynSendMessage(id,DATA_16,DYN_SPEED,1);
                dynSendMessage(id,DATA_16,DYN_CCW,0x3FF);
                dynSendMessage(id,DATA_16,DYN_POSITION,1023);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedJoin[j]);
            }else{
                dynSendMessage(id,DATA_16,DYN_POSITION,0x3FF);
                while(dynReadRegister(id,DATA_8,DYN_MOVING,3)){}
                dynSendMessage(id,DATA_16,DYN_CCW,0x00);
                dynSendMessage(id,DATA_16,DYN_SPEED,0);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedWheel[j]);
                int pos = 0x3FF;
                while((pos < 100)||(pos >900)){
                    pos = dynReadRegister(id,DATA_16,DYN_CURRENT_POSITION,4);
                }
                dynSendMessage(id,DATA_16,DYN_SPEED,1);
                dynSendMessage(id,DATA_16,DYN_CCW,0x3FF);
                dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedJoin[j]);
                dynSendMessage(id,DATA_16,DYN_POSITION,0);
            }
            cvs->dynamixels->cycle[j]++;

        }
    }
}

void dynSwitchMode(CtrlStruct *cvs,int id){
    if(id != DYN_ID_SUNSHADE){
    int j = map_id_index_dynamixels(id);
    
    if(cvs->dynamixels->dynamixelMode[j] == POSITION){
        cvs->dynamixels->dynamixelMode[j] = SPEED;
        dynSendMessage(id,DATA_16,DYN_CW,0x00);
        dynSendMessage(id,DATA_16,DYN_CCW,0x00);
    }else{
        cvs->dynamixels->dynamixelMode[j] = POSITION;
        dynSendMessage(id,DATA_16,DYN_CW,0x00);
        if(id == DYN_ID_GRIPPER_1 ||id == DYN_ID_GRIPPER_2){
            dynSendMessage(id,DATA_16,DYN_CCW,0x0FFF);
        }else{
            dynSendMessage(id,DATA_16,DYN_CCW,0x03FF);
        }
        dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedJoin[j]);
    }
    }
}
void dynSendMessage(int ID,int data_size,int address,int value){
    unsigned int Data1;
    unsigned int Data2;
    unsigned int Data3;
    unsigned int Data4;
    unsigned int Data5;
    unsigned int Data6;
    unsigned int Data7;
    unsigned int Data8;
    
    Data1 = ID & 0x000000FF;  //id 
    if(data_size == DATA_8){
        Data2 = 4;   //Length_L
    }
    else if(data_size == DATA_16){
        Data2 = 5;   //Length_L
    }else{
        Data2 = 3;   //Length_L
    }
    Data3 = 0x03;   //Instruction write in register
    Data5 = address;   //P0  	Write data start address LSB (ou 0x32)
    Data6 = (int) value & 0x00FF;   //P1        Write data start address MSB
    Data7 = ((int) value >> 8) & 0x00FF;   //P2        Write data 1st byte
    Data4 =  ~ ( Data1 + Data2 + Data3 + Data5 + Data6 + Data7);
    
    unsigned int Data_read = 0;
    int count = 0;
    //char display[1024];
    MyDelayMs(100);//Important
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x00); // Mise à 0 des commandes d'écritures
    MyCyclone_Write(CYCLONE_IO_dynDataWrite, 0x00); // Mise à 0 de TXD_Enable
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x14);
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x00); // Mise à 0 des commandes d'écritures
    MyCyclone_Write(CYCLONE_IO_dynDataWrite,(Data1&0x000000FF)+((Data2<<8)&0x0000FF00)+((Data3<<16)&0x00FF0000)+((Data4<<24)&0xFF000000));
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x15);//Ecriture de write1
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x00); // Mise à 0 des commandes d'écritures
    MyCyclone_Write(CYCLONE_IO_dynDataWrite,(Data5&0x000000FF)+((Data6<<8)&0x0000FF00)+((Data7<<16)&0x00FF0000));
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x16);//Ecriture de write2
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x00); // Mise à 0 des commandes d'écritures
    MyCyclone_Write(CYCLONE_IO_dynDataWrite,0x01);
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x14);
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x00);
}
int dynReadRegister(int ID,int data_size,int address,int try){
    int length_receive;
    
    unsigned int Data1;
    unsigned int Data2;
    unsigned int Data3;
    unsigned int Data4;
    unsigned int Data5;
    unsigned int Data6;
    unsigned int Data7;
    unsigned int Data8;
    
    Data1 = ID & 0x000000FF;  //id 
    Data2 = 4;   //Length_L
    Data3 = 0x02;   //Instruction read in register
    Data5 = address;   //P0  	Write data start address LSB (ou 0x32)
    if(data_size == DATA_8){
        Data6 = 0x1;   //P1
        length_receive = 3;
    }
    else if(data_size == DATA_16){
        Data6 = 0x2;   //P1
        length_receive = 4;
    }else{
        Data6 = 0x2;   //P1
        length_receive = 4;
    }
    Data7 = 0x0;   //P2
    Data4 =  ~ ( Data1 + Data2 + Data3 + Data5 + Data6 + Data7);
    
    unsigned int Data_read = 0;
    int count = 0;
    char display[1024];
    MyDelayMs(100);//Important
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x00); // Mise à 0 des commandes d'écritures
    MyCyclone_Write(CYCLONE_IO_dynDataWrite, 0x00); // Mise à 0 de TXD_Enable
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x14);
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x00); // Mise à 0 des commandes d'écritures
    MyCyclone_Write(CYCLONE_IO_dynDataWrite,(Data1&0x000000FF)+((Data2<<8)&0x0000FF00)+((Data3<<16)&0x00FF0000)+((Data4<<24)&0xFF000000));
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x15);//Ecriture de write1
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x00); // Mise à 0 des commandes d'écritures
    MyCyclone_Write(CYCLONE_IO_dynDataWrite,(Data5&0x000000FF)+((Data6<<8)&0x0000FF00)+((Data7<<16)&0x00FF0000));
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x16);//Ecriture de write2
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x00); // Mise à 0 des commandes d'écritures
    MyCyclone_Write(CYCLONE_IO_dynDataWrite,0x01);
    MyCyclone_Write(CYCLONE_IO_dynDrive,0x14);
    if(ID == DYN_ID_FISH_1){
        MyDelayMs(10);//Important
    }else{
        MyDelayMs(10);//Important
    }
    
    int RX_data = MyCyclone_Read(CYCLONE_IO_dynDataRead);
    
    if(((RX_data & 0xFF) == ID) & (((RX_data>>8) & 0xFF)==length_receive)){
        int value;
        if(data_size == DATA_16){
            value = 256*((RX_data>>24) & 0xFF)+((RX_data>>16) & 0xFF);
        }else{
            value = ((RX_data>>16) & 0xFF);
        }   
        if(ID==DYN_ID_GRIPPER_1 || ID==DYN_ID_GRIPPER_2){
            if((value < 4096) & (value >= 0)){
                sprintf(theStr,"%d \n",value);
                MyConsole_SendMsg(theStr);
                return value;
            }else if(try > 0){
                return dynReadRegister(ID,data_size,address,try-1);
            }else{
                return -1;
            } 
        }else{
            if((value < 1024) & (value >= 0)){
                return value;
            }else if(try > 0){
                return dynReadRegister(ID,data_size,address,try-1);
            }else{
                return -1;
            }
        } 
    }else if(try > 0){
        return dynReadRegister(ID,data_size,address,try-1);
    }else{
        return -1;
    }

}
void dynSwitch(CtrlStruct *cvs,int id){
    int j = map_id_index_dynamixels(id);
    if(cvs->dynamixels->dynamixelStart[j] == 0){
        cvs->dynamixels->dynamixelStart[j] = 1;
        dynSendMessage(id,DATA_16,DYN_SPEED,cvs->dynamixels->dynamixelSpeedWheel[j]);
    }else{
        cvs->dynamixels->dynamixelStart[j] = 0;
        dynSendMessage(id,DATA_16,DYN_SPEED,0);
    }
}
