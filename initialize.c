#include "variable.h"
extern void initialize(void)
{
	int i;
	for(i=0;i<8;i++)
	{
		windows[i].number=i+1;
		strcpy(windows[i].serveNo,"   ");
		windows[i].serveLen=0;
		windows[i].perserveLen=0;
		windows[i].wtime=0;
		windows[i].dtime=0;
		windows[i].rtime=0;
		windows[i].restLen=0;
		windows[i].custCount=0;
		windows[i].custnormCount=0;
		windows[i].custvipCount=0;
		windows[i].custsatisfyGood=0;
		windows[i].custsatisfyNorm=0;
		windows[i].custsatisfyBad=0;
		windows[i].flag=0;
		if(i==1||i>=5)
		{
			windows[i].state=CLOSE;//¹Ø±Õ×´Ì¬		
		}
		else 
		{
			windows[i].state=FREE;// ¿ÕÏÐ×´Ì¬ 
		}
	}
}

