#include <stdio.h>

int checksum(unsigned int data1,unsigned int data2)
{
    //printf("data1 = %x \n",data1);
    //printf("data2 = %x \n",data2);

    unsigned int id = data1 & 0x000000FF;
    unsigned int length = (data1 & 0x0000FF00) >> 8;
    unsigned int instr = (data1 & 0x00FF0000) >> 16;
    unsigned int P0 = data2 & 0x000000FF;
    unsigned int P1 = (data2 & 0x0000FF00) >> 8;
    unsigned int P2 = (data2 & 0x00FF0000) >> 16;

/*
    printf("id = %x \n",id);
    printf("length = %x \n",length);
    printf("instr = %x \n",instr);
    printf("P0 = %x \n",P0);
    printf("P1 = %x \n",P1);
    printf("P2 = %x \n",P2);
    */

    int check = (~(id+length+instr+P0+P1+P2)) & 0x000000FF;

    //printf("check = %x \n",check);

    return check;
}
