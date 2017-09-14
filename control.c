#include<stdlib.h>
#include<stdio.h>
#include "variable.h"

/*控制普通客户的链表，分配普通客户*/ 
static void controlnorm(void)
{
	extern int size1;
	int i,j;
	LISTNODEPTR tempPtr=NULL;
	for(i=2;i<8;i++)//窗口3--后是普通窗口 
	{
		if(((windows[i].state==FREE)||(windows[i].state==FINISH))&&(normServeLen>=3*size1)&&(headp!=NULL))//窗口是空闲状态 
		{
			tempPtr=headp;
			headp=headp->nextPtr;
			if(headp==NULL)//如果已经结束，则将tailp赋值为NULL 
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
			if(headp==NULL)//如果已经结束，则将tailp赋值为NULL 
			{
				tailp=NULL;	
			}
			strcpy(windows[i].serveNo,tempPtr->num);
			normServeLen--;
			free(tempPtr);			
		}
	}
}
/*控制vip客户链表，分配vip客户*/ 
static void controlvip(void)
{
	extern size2;
	int i;
	LISTNODEPTR tempPtr=NULL;
	for(i=0;i<2;i++)
	{
		if((windows[i].state==FREE||windows[i].state==FINISH)&&(vipServeLen>3)&&(headpVIP!=NULL))//窗口为空闲并且有vip客户 
		{
			tempPtr=headpVIP;
			headpVIP=headpVIP->nextPtr;//将此客户分配给窗口 
			if(headpVIP==NULL)
			{
				tailpVIP=NULL; 
			}
			strcpy(windows[i].serveNo,tempPtr->num);//拷贝字符串
			vipServeLen--;
			free(tempPtr);
		}
		
		else if((windows[i].state==FREE||windows[i].state==FINISH)&&(windows[i].flag==0)&&(vipServeLen<=3)&&(i==0)&&(headpVIP!=NULL))
		{
			tempPtr=headpVIP;
			headpVIP=headpVIP->nextPtr;//将此客户分配给窗口 
			if(headpVIP==NULL)
			{
				tailpVIP=NULL;
			}
			strcpy(windows[i].serveNo,tempPtr->num);//拷贝字符串
			vipServeLen--;
			free(tempPtr);			
		}
		else if((strategy==2)&&(windows[i].state==FREE||windows[i].state==FINISH)&&(headpVIP==NULL)&&(headp!=NULL))//若窗口空闲并且vip人数为0，普通客户人数不为0，则顺便服务 
		{
			tempPtr=headp;
			headp=headp->nextPtr;
			if(headp==NULL)
			{
				tailp=NULL;
			}
			strcpy(windows[i].serveNo,tempPtr->num);//拷贝字符串 
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
/*找到最短休息时间的窗口*/
static WINTORESTPTR findrw(void)//返回休息窗口的那个链表 
{
	WINTORESTPTR aPtr=NULL,tempPtr=NULL;
	int win,min,temp;//下标，最短休息时长，时间； 
	if(headpWinRest!=NULL)
	{
		aPtr=headpWinRest;
		win=(aPtr->restwin)-1;
		min=windows[win].restLen;
		tempPtr=aPtr;
		temp=aPtr->t;//时间比较标准 
		
		aPtr=aPtr->nextPtr;
		while((aPtr!=NULL)&&((aPtr->t)==temp))
		{
			if(min>(windows[(aPtr->restwin)-1].restLen))
			{
				min=windows[(aPtr->restwin)-1].restLen;
				tempPtr=aPtr;//不断保存此时最小休息时间所对应的aPtr 
			}
			aPtr=aPtr->nextPtr;
		}
	}
	return tempPtr;
}
/*控制休息窗口*/ 
static void controlrest(void)
{
	WINTORESTPTR rPtr=NULL,previousPtr=NULL;
	int j;//J为最短时长所对应的窗口下标 
	if(headpWinRest!=NULL)
	{	
		if(((headpWinRest->restwin)==0)&&close==1)//下班请求 
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
			if(rPtr==headpWinRest)//若就是第一个 
			{
				headpWinRest=headpWinRest->nextPtr;
			}
			else//若不是第一个，找rPtr的前一个节点 
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
		else if(size1>=4&&normServeLen<MaxSeqLen1&&(headpWinRest->restwin)>=3)//只有当窗口满足最小开放数时，才能允许休息申请 
		{
			rPtr=findrw();
			j=(rPtr->restwin)-1;
				if((windows[j].state==FINISH)||(windows[j].state==FREE))
			{
			windows[j].flag=1;
			if(rPtr==headpWinRest)//若就是第一个 
			{
				headpWinRest=headpWinRest->nextPtr;
			}
			else//若不是第一个，找rPtr的前一个节点 
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
