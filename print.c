#include<stdio.h>
#include "variable.h"
extern void print_message(FILE* destfPtr)
{
	int i=0;
	
	fprintf(destfPtr,"T=%2d\n",timeCount);
	for(i=0;i<=7;i++)
	{
		fprintf(destfPtr,"WIN:%d\t",i+1);
		if(windows[i].state==0)
		{
			fprintf(destfPtr,"State=%s\t","CLOSE");
		}
		else if(windows[i].state==1)
		{
			fprintf(destfPtr,"State=%s\t","FREE");
		}
		else if(windows[i].state==2)
		{
			fprintf(destfPtr,"State=%s\t","WAIT");
		}	
		else if(windows[i].state==3)
		{
			fprintf(destfPtr,"State=%s\t","DEAL");
		}			
		else if(windows[i].state==4)
		{
			fprintf(destfPtr,"State=%s\t","FINISH");
		}
		else if(windows[i].state==5)
		{
			fprintf(destfPtr,"State=%s\t","PAUSE");
		}
		//fprintf(destfPtr,"WIN %d:State=%-10d",i,windows[i].state);
		fprintf(destfPtr,"ServeNo=%s\t",windows[i].serveNo);
		fprintf(destfPtr,"ServeLen=%d/%d\tRestLen=%d/%d\t\n",windows[i].serveLen,windows[i].plandtime,windows[i].restLen,windows[i].planrtime);
	//	fflush(destfPtr);
	}
}
extern void printStatistics(FILE* destfPtr)
{
	int i=0;
	int totalcustNormCom=0,totalcustVipCount=0,max=0,n=0,m,k,j;
	int satisfynotgood[7]={0};
	for(i=0;i<=7;i++)
	{
		fprintf(destfPtr,"WIN %d:custCount=%10d,custnormCount=%10d,custvipCount=%10d,custsatisfyGood=%10d,custsatisfyNorm=%10d,custsatisfyBad=%10d\n",
				windows[i].number,windows[i].custCount,windows[i].custnormCount,windows[i].custvipCount,
				windows[i].custsatisfyGood,windows[i].custsatisfyNorm,windows[i].custsatisfyBad);
		totalcustNormCom=totalcustNormCom+windows[i].custnormCount;
		totalcustVipCount=totalcustVipCount+windows[i].custvipCount;
		m=windows[i].custsatisfyGood;
		k=windows[i].custCount;
		j=windows[i].custsatisfyBad;
		if((double)m/k<0.7||(double)j/k>0.1)
			{
				satisfynotgood[n]=1;   //表示满意的客户占总客户数小于70%，或者表示不满意的客户占总客户数>10%
				n++;
			}	
	}	
	fprintf(destfPtr,"totalcustNormCom=%d\ntotalcustVipCount=%d\nsatisfynotgoodwin=\n",
			totalcustNormCom,totalcustVipCount);
	for(i=0;i<=7;i++)
		{
			if(satisfynotgood[n]==1)
			fprintf(destfPtr,"%d ",n+1);
		}
	fprintf(destfPtr,"\n");
}


static void printlist(FILE* destfPtr)
{
	LISTNODEPTR currentnormPtr,currentvipPtr;
	currentnormPtr=headp;
	currentvipPtr=headpVIP;
	fprintf(destfPtr,"normList:");
	while(currentnormPtr!=NULL)
	{
		fprintf(destfPtr,"%s->",currentnormPtr->num);
		currentnormPtr=currentnormPtr->nextPtr;
	}
	fprintf(destfPtr,"\n");
	fprintf(destfPtr,"vipList:");
	while(currentvipPtr!=NULL)
	{
		fprintf(destfPtr,"%s->",currentvipPtr->num);
		currentvipPtr=currentvipPtr->nextPtr;
	}
	fprintf(destfPtr,"\n");
}

static void printScreen1(void)
{
	int i=0;
	printf("T=%2d\n",timeCount);
	for(i=0;i<=7;i++)
	{
		printf("WIN:%d\t",i+1);
		if(windows[i].state==0)
		{
			printf("State=%s\t","CLOSE");
		}
		else if(windows[i].state==1)
		{
			printf("State=%s\t","FREE");
		}
		else if(windows[i].state==2)
		{
			printf("State=%s\t","WAIT");
		}	
		else if(windows[i].state==3)
		{
			printf("State=%s\t","DEAL");
		}			
		else if(windows[i].state==4)
		{
			printf("State=%s\t","FINISH");
		}
		else if(windows[i].state==5)
		{
			printf("State=%s\t","PAUSE");
		}
		fflush(stdout);
		//fprintf(destfPtr,"WIN %d:State=%-10d",i,windows[i].state);
		printf("ServeNo=%s\t",windows[i].serveNo);
		fflush(stdout);
		printf("ServeLen=%3d/%3d\tRestLen=%3d/%3d\t\n",windows[i].serveLen,windows[i].plandtime,windows[i].restLen,windows[i].planrtime);
		fflush(stdout);
	}
}



static void printScreen2(void)
{
	LISTNODEPTR currentnormPtr,currentvipPtr;
	currentnormPtr=headp;
	currentvipPtr=headpVIP;
	printf("normList:");
	while(currentnormPtr!=NULL)
	{
		printf("%s->",currentnormPtr->num);
		currentnormPtr=currentnormPtr->nextPtr;
	} 
	printf("\n");
	printf("vipList:");
	while(currentvipPtr!=NULL)
	{
		printf("%s->",currentvipPtr->num);
		currentvipPtr=currentvipPtr->nextPtr;
	}
	printf("\n");
}


extern void printScreen3(void)
{
	int i=0;
	int totalcustNormCom=0,totalcustVipCount=0,max=0,n=0,m,k,j;
	int satisfynotgood[7]={0};
	for(i=0;i<=7;i++)
	{
		printf("WIN %d:总客户数：%3d,普通客户：%3d,VIP客户：%3d,好评：%3d,中评：%3d,差评：%3d\n",
				windows[i].number,windows[i].custCount,windows[i].custnormCount,windows[i].custvipCount,
				windows[i].custsatisfyGood,windows[i].custsatisfyNorm,windows[i].custsatisfyBad);
		totalcustNormCom=totalcustNormCom+windows[i].custnormCount;
		totalcustVipCount=totalcustVipCount+windows[i].custvipCount;
		m=windows[i].custsatisfyGood;
		k=windows[i].custCount;
		j=windows[i].custsatisfyBad;
		if((double)m/k<0.7||(double)j/k>0.1)
			{
				satisfynotgood[i]=1;   //表示满意的客户占总客户数小于70%，或者表示不满意的客户占总客户数>10%
			}	
	}	
	printf("totalcustNormCom=%d\ntotalcustVipCount=%d\nsatisfynotgoodwin=",
			totalcustNormCom,totalcustVipCount);
	for(i=0;i<=7;i++)
		{
			if(satisfynotgood[i]==1)
			printf("%d ",i+1);
		}
	printf("\n");
}



extern void print1(FILE* destfPtr)
{
		print_message(destfPtr);
		printlist(destfPtr);
		printScreen1();
		printScreen2();
}

extern void print2(FILE* destfPtr)
{
	print_message(destfPtr);
	printlist(destfPtr);
}

