#include <stdio.h>
#include"checksum.h"


int checksum(unsigned int id,unsigned int length,unsigned int instr,unsigned int P0,unsigned int P1,unsigned int P2)
{
    int check = (~(id+length+instr+P0+P1+P2)) & 0x000000FF;
    return check;
}
