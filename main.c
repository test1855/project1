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
int ischange=0,close=0,over=0;//�ֱ��Ǵ�ӡ�б仯����Ϣ   �յ��°�����    �ر�Ӫҵ�� 
int strategy=1;//1ΪVIP�������2ΪVIP˳����� 
WINDOW windows[8];
LISTNODEPTR headp=NULL;         		LISTNODEPTR tailp=NULL;//ָ����ͨ�ͻ�����ͷָ��,βָ��
LISTNODEPTR headpVIP=NULL;      		LISTNODEPTR tailpVIP=NULL;//ָ��VIP�ͻ�����ͷָ�룬βָ�� 
WINTORESTPTR headpWinRest=NULL; 		WINTORESTPTR tailpWinRest=NULL;//ָ�򴰿�������Ϣ����ͷָ�룬βָ��
HANDLE hClientMutex;

EVENT_TYPE ev;

int main()
{
	
	int num;
	
	FILE *cfPtr;//vip����ά�� 
    int choice;
	int way;
	FILE *fPtr1=NULL;//����Ӫҵ 
	FILE *fPtr2=NULL;
	FILE *fPtr3=NULL;
	FILE *fPtr4=NULL;
	FILE *vipPtr=NULL;
	   
//	HEGG egg1,egg2; 
	
	fileWrite();
	printInitial();
	fileRead();

	initialize();

	printf("\t\t************************************\n\t\t\t   С��201421130205\n\t  ***********************************************\t\t\t\t\t\t ��ӭ����ȫ���һ�ȵĴ�������Ů����\n\t\t  ***********************************\n\t\t      ���������ᣬ������·��\n\t\t\t******************\n");
	printf("������������е�����\n"
			"1--vip����ά��\n"
			"2--�����ļ�ά��\n"
			"3--��ͨ���п�ʼӪҵ\n"
			"4--�������п�ʼӪҵ\n");
	scanf("%d",&num);
	while(num!=3&&num!=4)
		{
			switch(num)
				{
					case 1:
						while((choice=enterChoice())!=4)
							{            /*����Ϊ4ʱ�˳�*/   
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
						fileUpdate();    //�����ļ�ά�� 
						printInitial();
						fileRead();
						break;
				}
			printf("������������е�����\n"
				"1--vip����ά��\n"
				"2--�����ļ�ά��\n"
				"3--���п�ʼӪҵ\n"
				"4--�������п�ʼӪҵ\n");
			scanf("%d",&num);
		}
	if(num==3)
	{
		printf("��ѡ�����뷽ʽ��\n1--�ļ�����\n2--��������\n");
		scanf("%d",&way); 
	
 		printf("������������еĲ��ԣ�\n1--VIP���ڶ���������\n2--VIP����˳��������\n");
		scanf("%d",&strategy);
		fileRead();

		initialize();

		if((fPtr2=fopen("outputDetail.txt","w"))==NULL)//�����Դ�ӡ 
		{
			printf("destfPtr");
		}
		else if((fPtr3=fopen("output.txt","w"))==NULL)//״̬�仯�Ĵ�ӡ 
		{
			printf("NNN");		
		}
		else if((fPtr4=fopen("ͳ����Ϣ.txt","w"))==NULL)
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
		if((fPtr2=fopen("outputDetail.txt","w"))==NULL)//�����Դ�ӡ 
		{
			printf("destfPtr");
		}
		else if((fPtr3=fopen("output.txt","w"))==NULL)//״̬�仯�Ĵ�ӡ 
		{
			printf("NNN");		
		}
		else if((fPtr4=fopen("ͳ����Ϣ.txt","w"))==NULL)
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








