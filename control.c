#include<stdlib.h>
#include<stdio.h>
#include "variable.h"

/*������ͨ�ͻ�������������ͨ�ͻ�*/ 
static void controlnorm(void)
{
	extern int size1;
	int i,j;
	LISTNODEPTR tempPtr=NULL;
	for(i=2;i<8;i++)//����3--������ͨ���� 
	{
		if(((windows[i].state==FREE)||(windows[i].state==FINISH))&&(normServeLen>=3*size1)&&(headp!=NULL))//�����ǿ���״̬ 
		{
			tempPtr=headp;
			headp=headp->nextPtr;
			if(headp==NULL)//����Ѿ���������tailp��ֵΪNULL 
			{
				tailp=NULL;	
			}
			strcpy(windows[i].serveNo,tempPtr->num);
			normServeLen--;
			free(tempPtr);
		}
		else if(((windows[i].state==FREE)||(windows[i].state==FINISH))&&(windows[i].flag==0)&&(normServeLen<3*size1)&&(headp!=NULL))
		{
			tempPtr=headp;
			headp=headp->nextPtr;
			if(headp==NULL)//����Ѿ���������tailp��ֵΪNULL 
			{
				tailp=NULL;	
			}
			strcpy(windows[i].serveNo,tempPtr->num);
			normServeLen--;
			free(tempPtr);			
		}
	}
}
/*����vip�ͻ���������vip�ͻ�*/ 
static void controlvip(void)
{
	extern size2;
	int i;
	LISTNODEPTR tempPtr=NULL;
	for(i=0;i<2;i++)
	{
		if((windows[i].state==FREE||windows[i].state==FINISH)&&(vipServeLen>3)&&(headpVIP!=NULL))//����Ϊ���в�����vip�ͻ� 
		{
			tempPtr=headpVIP;
			headpVIP=headpVIP->nextPtr;//���˿ͻ���������� 
			if(headpVIP==NULL)
			{
				tailpVIP=NULL; 
			}
			strcpy(windows[i].serveNo,tempPtr->num);//�����ַ���
			vipServeLen--;
			free(tempPtr);
		}
		
		else if((windows[i].state==FREE||windows[i].state==FINISH)&&(windows[i].flag==0)&&(vipServeLen<=3)&&(i==0)&&(headpVIP!=NULL))
		{
			tempPtr=headpVIP;
			headpVIP=headpVIP->nextPtr;//���˿ͻ���������� 
			if(headpVIP==NULL)
			{
				tailpVIP=NULL;
			}
			strcpy(windows[i].serveNo,tempPtr->num);//�����ַ���
			vipServeLen--;
			free(tempPtr);			
		}
		else if((strategy==2)&&(windows[i].state==FREE||windows[i].state==FINISH)&&(headpVIP==NULL)&&(headp!=NULL))//�����ڿ��в���vip����Ϊ0����ͨ�ͻ�������Ϊ0����˳����� 
		{
			tempPtr=headp;
			headp=headp->nextPtr;
			if(headp==NULL)
			{
				tailp=NULL;
			}
			strcpy(windows[i].serveNo,tempPtr->num);//�����ַ��� 
			normServeLen--;
			free(tempPtr);		
		}
	
		if(vipServeLen>=3&&size2<2&&windows[1].state==0)
		{
			windows[1].state=1;
			size2++;
		}
	}
}
/*�ҵ������Ϣʱ��Ĵ���*/
static WINTORESTPTR findrw(void)//������Ϣ���ڵ��Ǹ����� 
{
	WINTORESTPTR aPtr=NULL,tempPtr=NULL;
	int win,min,temp;//�±꣬�����Ϣʱ����ʱ�䣻 
	if(headpWinRest!=NULL)
	{
		aPtr=headpWinRest;
		win=(aPtr->restwin)-1;
		min=windows[win].restLen;
		tempPtr=aPtr;
		temp=aPtr->t;//ʱ��Ƚϱ�׼ 
		
		aPtr=aPtr->nextPtr;
		while((aPtr!=NULL)&&((aPtr->t)==temp))
		{
			if(min>(windows[(aPtr->restwin)-1].restLen))
			{
				min=windows[(aPtr->restwin)-1].restLen;
				tempPtr=aPtr;//���ϱ����ʱ��С��Ϣʱ������Ӧ��aPtr 
			}
			aPtr=aPtr->nextPtr;
		}
	}
	return tempPtr;
}
/*������Ϣ����*/ 
static void controlrest(void)
{
	WINTORESTPTR rPtr=NULL,previousPtr=NULL;
	int j;//JΪ���ʱ������Ӧ�Ĵ����±� 
	if(headpWinRest!=NULL)
	{	
		if(((headpWinRest->restwin)==0)&&close==1)//�°����� 
		{
			if(headp==NULL&&headpVIP==NULL)
			{
				for(j=0;j<8;j++)
				{
					strcpy(windows[j].serveNo,"   ");
					windows[j].state=0;
				}
			}
		}
		else if((close==0)&&(size2==2)&&(vipServeLen<3)&&(headpWinRest->restwin)<=2)
		{
			rPtr=findrw();
			j=(rPtr->restwin)-1;
			if((windows[j].state==FINISH)||(windows[j].state==FREE))
			{
				
			
			windows[j].flag=1;
			if(rPtr==headpWinRest)//�����ǵ�һ�� 
			{
				headpWinRest=headpWinRest->nextPtr;
			}
			else//�����ǵ�һ������rPtr��ǰһ���ڵ� 
			{
				previousPtr=headpWinRest;
				while((previousPtr->nextPtr)!=rPtr)
				{
					previousPtr=previousPtr->nextPtr;	
				}
				
				if(rPtr->nextPtr==NULL)
				{
					tailpWinRest=previousPtr;
					previousPtr->nextPtr=NULL;
				}
				else
				{
					previousPtr->nextPtr=rPtr->nextPtr;
				}
			}
			}
		}
		else if(size1>=4&&normServeLen<MaxSeqLen1&&(headpWinRest->restwin)>=3)//ֻ�е�����������С������ʱ������������Ϣ���� 
		{
			rPtr=findrw();
			j=(rPtr->restwin)-1;
				if((windows[j].state==FINISH)||(windows[j].state==FREE))
			{
			windows[j].flag=1;
			if(rPtr==headpWinRest)//�����ǵ�һ�� 
			{
				headpWinRest=headpWinRest->nextPtr;
			}
			else//�����ǵ�һ������rPtr��ǰһ���ڵ� 
			{
				previousPtr=headpWinRest;
				while((previousPtr->nextPtr)!=rPtr)
				{
					previousPtr=previousPtr->nextPtr;	
				}
				
				if(rPtr->nextPtr==NULL)
				{
					tailpWinRest=previousPtr;
					previousPtr->nextPtr=NULL;
				}
				else
				{
					previousPtr->nextPtr=rPtr->nextPtr;
				}	
			}
			free(rPtr);
		}
	}
	}
}

extern void control(void)
{
	int i;
	controlnorm();
	controlvip();
	controlrest();
	for(i=0;i<8;i++)
	{
		if(windows[i].state!=CLOSE)
		{
			break;
		}
	}
	if(i==8)
		over=1;
}
