/*
 * this function creates a tab based on the argugments from char0 to char3
 * forCAN is true when data is a tab of length 3
 */

#include "globals.h"
#include <math.h>

void makeData( char* data,  char data0,  char data1, 
			 char data2, char data3, bool forCAN)
{
    if(forCAN)
    {
        data[0] = data0;
        data[1] = data1;
        data[2] = data2;
        
    }
    else
    {
        data[0] = data0;
        data[1] = data1;
        data[2] = data2;
        data[3] = data3;
    }
}

int spi2data (char* data)
{
    int output = (int) data[0] + (256*data[1]) + (256*256*data[1]) + (256*256*256*data[3]);
}


int maxdata(int data1, int data2)
{
    int max;
    if(data1 >= data2)
    {
        max = data1;
    }
    else
    {
        max = data2;
    }
    return max;
}

