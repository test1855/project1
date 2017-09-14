#include<stdio.h>
#include<stdlib.h>
#include"variable.h"

void bank1(FILE* sourcefPtr,FILE* destfPtr,FILE* destfPtr1,FILE* destfPtr2)
{
	int readtime=0;
	while(headp!=NULL||headpVIP!=NULL||close!=1||over!=1)
	{
		ischange=0;
		if(!feof(sourcefPtr))
		{
			if(readtime==0)
			{
				fscanf(sourcefPtr,"T=%d,",&readtime);
			}
			if(readtime==timeCount)
			{
				get_input(sourcefPtr);
				readtime=0;
			}
		}

		control();
		state_trans();
		print1(destfPtr);
		
		if(ischange==1)
		{
			print2(destfPtr1);
		}
		timeCount++;
	}
	printStatistics(destfPtr2);
	printScreen3();
}

