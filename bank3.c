#include <stdio.h>
#include <stdlib.h>
#include "egg.h"
#include "variable.h"

void bank3(FILE * destfPtr,FILE *destfPtr1,FILE *destfPtr2)
{
	double X,Y;
	StartTimer(1000);
	while((ev=WaitForEvent())!=EXIT)
	{
		switch(ev)
			{
				case TIMER:
					control();
					state_trans();
					eggstate_trans();
					queue();
					break;
				case KEYDOWN:   
					if(close==0)
					{
						getNum();
						getrest();
					}
					break;			
			}
		if(close==1&&headp==NULL&&headpVIP==NULL&&over==1)
		{
			break;
		}
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
 

					
		
