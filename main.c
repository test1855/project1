#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "vipprotect.h"

#include "fileprotect.h"

#include "variable.h"

#include "egg.h"

int MaxSeqLen1,MinSec1,MaxSec1,MinRestSec1,MaxRestSec1,VIPSERVLen1,WaitTime1;
int countG=0,countV=0,countR=0;
int normServeLen=0,vipServeLen=0;
int size1=3,size2=1;
int timeCount=1;
int ischange=0,close=0,over=0;//分别是打印有变化的信息   收到下班请求    关闭营业厅 
int strategy=1;//1为VIP定向服务，2为VIP顺便服务 
WINDOW windows[8];
LISTNODEPTR headp=NULL;         		LISTNODEPTR tailp=NULL;//指向普通客户队列头指针,尾指针
LISTNODEPTR headpVIP=NULL;      		LISTNODEPTR tailpVIP=NULL;//指向VIP客户队列头指针，尾指针 
WINTORESTPTR headpWinRest=NULL; 		WINTORESTPTR tailpWinRest=NULL;//指向窗口申请休息队列头指针，尾指针
HANDLE hClientMutex;

EVENT_TYPE ev;

int main()
{
	
	int num;
	
	FILE *cfPtr;//vip资料维护 
    int choice;
	int way;
	FILE *fPtr1=NULL;//银行营业 
	FILE *fPtr2=NULL;
	FILE *fPtr3=NULL;
	FILE *fPtr4=NULL;
	FILE *vipPtr=NULL;
	   
//	HEGG egg1,egg2; 
	
	fileWrite();
	printInitial();
	fileRead();

	initialize();

	printf("\t\t************************************\n\t\t\t   小组201421130205\n\t  ***********************************************\t\t\t\t\t\t 欢迎来到全球第一萌的代码美少女银行\n\t\t  ***********************************\n\t\t      我们正年轻，我们在路上\n\t\t\t******************\n");
	printf("请输入您想进行的任务\n"
			"1--vip资料维护\n"
			"2--配置文件维护\n"
			"3--普通银行开始营业\n"
			"4--动画银行开始营业\n");
	scanf("%d",&num);
	while(num!=3&&num!=4)
		{
			switch(num)
				{
					case 1:
						while((choice=enterChoice())!=4)
							{            /*输入为4时退出*/   
				 					switch(choice)
									{
            							case 1:
	               							if((cfPtr=fopen("vip.txt","rb+"))==NULL)
												printf("File could not be opened.\n");
	 	          							else
		                						updateRecord(cfPtr);
	               			 				break;
										case 2:
                 		   					if((cfPtr=fopen("vip.txt","rb+"))==NULL)
	                   							printf("File could not be opened.\n");
	                						else
 		            							addRecord(cfPtr);
	                						break;
										case 3:
	                						if((cfPtr=fopen("vip.txt","rb+"))==NULL)
			         							printf("File could not be opened.\n");
	         								else
		                						deleteRecord(cfPtr);
	                						break;
 	           						}   
           					}
           			           
						break;
					case 2:
						fileUpdate();    //配置文件维护 
						printInitial();
						fileRead();
						break;
				}
			printf("请输入您想进行的任务\n"
				"1--vip资料维护\n"
				"2--配置文件维护\n"
				"3--银行开始营业\n"
				"4--动画银行开始营业\n");
			scanf("%d",&num);
		}
	if(num==3)
	{
		printf("请选择输入方式：\n1--文件输入\n2--键盘输入\n");
		scanf("%d",&way); 
	
 		printf("请输入您想进行的策略：\n1--VIP窗口定向服务策略\n2--VIP窗口顺便服务策略\n");
		scanf("%d",&strategy);
		fileRead();

		initialize();

		if((fPtr2=fopen("outputDetail.txt","w"))==NULL)//周期性打印 
		{
			printf("destfPtr");
		}
		else if((fPtr3=fopen("output.txt","w"))==NULL)//状态变化的打印 
		{
			printf("NNN");		
		}
		else if((fPtr4=fopen("统计信息.txt","w"))==NULL)
		{
			printf("yyy");
		}
		else
		{
			if((fPtr1=fopen("input.txt","r"))==NULL)
			{
				printf("soucefPtr");
			}	
			else if(way==1)
			{
				bank1(fPtr1,fPtr2,fPtr3,fPtr4);
				fclose(fPtr1);
			}	
			else if(way==2)
			{
				bank2(fPtr2,fPtr3,fPtr4);
			}
		}
		fclose(fPtr2);
		fclose(fPtr3);
		fclose(fPtr4);
	}
	else if(num==4)
	{
		if((fPtr2=fopen("outputDetail.txt","w"))==NULL)//周期性打印 
		{
			printf("destfPtr");
		}
		else if((fPtr3=fopen("output.txt","w"))==NULL)//状态变化的打印 
		{
			printf("NNN");		
		}
		else if((fPtr4=fopen("统计信息.txt","w"))==NULL)
		{
			printf("yyy");
		}
		else 
		{
			EggStart(1300,700);
			tietu1();
			opendoor();
			bank3(fPtr2,fPtr3,fPtr4);
			closedoor();
		}
		fclose(fPtr2);
		fclose(fPtr3);
		fclose(fPtr4);
		fclose(vipPtr);
	}
	system("pause");
	return 0;  
}








