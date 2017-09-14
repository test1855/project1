#include<stdio.h>
#include<time.h>
#include"variable.h"
extern int MaxSeqLen1,MinSec1,MaxSec1,MinRestSec1,MaxRestSec1,VIPSERVLen1,WaitTime1;
extern void state_trans(void)//WINDOW windows[],int size,......)普通客户 
{
    int i,degree;
    int arrival,sign,stop;
	for(i=0;i<8;i++)
	{
		switch(windows[i].state)
   		{
   			case CLOSE://关闭 
   				if(i>1&&close==0&&normServeLen>=3*size1)//动态打开普通窗口 
   				{
   					windows[i].state=FREE;
   					ischange=1;
   					size1++;
				}
				else if(i<=1&&close==0&&vipServeLen>=3)//动态打开vip窗口 
				{
					windows[i].state=FREE;
					ischange=1;
					size2++;
				}
   				break;
   			case FREE://空闲:
      			if(strcmp(windows[i].serveNo,"   ")!=0)//接到任务)
  				{
  					windows[i].state=WAIT;//状态切换到“等待顾客”;
  					ischange=1;
                    windows[i].wtime++;//启动等待计时;          
       			}
                else if((windows[i].flag==1)&&(i>1)&&(size1>3))//有休息请求，且请求被通过)
  				{	
                  	windows[i].state=PAUSE;//状态切换到“暂停”;
                  	ischange=1;
                  	size1--;
                  	srand(time(NULL));
                  	stop=MinRestSec1+rand()%(MaxRestSec1-MinRestSec1+1);
                  	windows[i].resttime=stop;
                  	windows[i].planrtime=stop;
					windows[i].rtime++;//启动休息计时;
					windows[i].restLen++;
              	}
              	else if((windows[i].flag==1)&&(i<=1)&&(size2==2))//有休息请求，且请求被通过)
  				{	
                  	windows[i].state=PAUSE;//状态切换到“暂停”;
                  	ischange=1;
                  	size2--;
                  	srand(time(NULL));
                  	stop=MinRestSec1+rand()%(MaxRestSec1-MinRestSec1+1);
                  	windows[i].resttime=stop;
                  	windows[i].planrtime=stop;
					windows[i].rtime++;//启动休息计时;
					windows[i].restLen++;
              	}
              	else if((i==size1+1)&&(close==0)&&(normServeLen<3*size1)&&(size1>3))//动态关闭多余的普通窗口 
				{
					windows[i].state=CLOSE;
					ischange=1;
					size1--;
				}
				else if((i>1)&&(close==1)&&(headp==NULL))//下班后关闭窗口 
				{
					windows[i].state=CLOSE;
					ischange=1;
					size1--;
				}
				else if((i==size2-1)&&(close==0)&&(vipServeLen<3)&&(size2==2))//关闭多余的vip窗口 
				{
					windows[i].state=CLOSE;
					ischange=1;
					size2--;
				}
				else if((i<=1)&&(close==1)&&(headpVIP==NULL))//下班后关闭vip窗口 
				{
					windows[i].state=CLOSE;
					ischange=1;
					size2--;
				}
              	break;
          	  	case WAIT://等待顾客：
              	srand(time(NULL));
              	arrival=rand()%2;//随机数模拟顾客是否到来；
	          	if(arrival==0&&windows[i].wtime<WaitTime1)//顾客未到达且等待未超时)
                {
                	windows[i].wtime++;
                } //do nothing
              	else if(arrival==0&&windows[i].wtime>=WaitTime1)//顾客未到达且等待时间到)
                {
                	windows[i].wtime=0;
                	windows[i].state=FREE;
                	ischange=1;
                	strcpy(windows[i].serveNo,"   ");
                	
                } //转为“空闲"状态;......
              	else if(arrival==1&&windows[i].wtime<WaitTime1)//顾客到达且等待时间未超时)
                {
                	windows[i].wtime=0;
         			windows[i].state=DEAL;
         			ischange=1;
         			windows[i].custCount++;
         			if(windows[i].serveNo[0]=='V')
					{
						windows[i].custvipCount++;
					} 
					else 
					{
         				windows[i].custnormCount++; 
         			}
         			srand(time(NULL));                             //开始不一样 
          			sign=MinSec1+rand()%(MaxSec1-MinSec1+1); 
          			windows[i].dealtime=sign;
          			windows[i].plandtime=windows[i].plandtime+sign;			//结束不一样 
                } //转为“办理中”状态;启动服务计时;......
			  	break;
          	case DEAL://办理中：
				if(windows[i].dtime<windows[i].dealtime)//未达到计划办理时间 
				{
					windows[i].serveLen++;
					windows[i].dtime++;
				}//donothing
				else if(windows[i].dtime>=windows[i].dealtime)		//开始不一样   
				{
				//	windows[i].serveLen++
               		windows[i].dtime=0;
               		windows[i].dealtime=0;
	               	windows[i].state=FINISH;
					ischange=1;	
	           		strcpy(windows[i].serveNo,"   ");	  
       			}//转换为”办理结束“状态;
	       		break;
      		case FINISH://办理结束：
      			srand(time(NULL));
      			degree=rand()%3;
      			switch(degree)
      			{
      				case 0:
      					(windows[i].custsatisfyGood)++;
     					break;
   					case 1:
   						(windows[i].custsatisfyNorm)++;
  						break;
					case 2:
						(windows[i].custsatisfyBad)++;
						break;
			      	
		      	}
				if((strcmp(windows[i].serveNo,"   "))!=0)//接到任务)
    			{
			    	windows[i].state=WAIT;
			    	ischange=1;
			    }//转换为“等待顾客”状态;
			    else if(windows[i].flag==1)
			    {
			    	windows[i].state=PAUSE;//状态切换到“暂停”;
                  	ischange=1;
                  	size1--;
                  	srand(time(NULL));
					stop=MinRestSec1+rand()%(MaxRestSec1-MinRestSec1+1);
                  	windows[i].resttime=stop;
                  	windows[i].planrtime=stop;
					windows[i].rtime++;//启动休息计时;	
              		windows[i].restLen++;
				}//有休息请求，转换为暂停状态 */
 				else//无任务）
   				{
			    	windows[i].state=FREE;
			    	ischange=1;
			    }//转换为“空闲”状态;
      			break;
	      	case PAUSE://暂停：
				if(windows[i].rtime<windows[i].resttime)
				{
					windows[i].rtime++;
					windows[i].restLen++;  //不一样 
				}
				else if((windows[i].rtime)>=(windows[i].resttime))   //开始不一样 
				{
					if(i>1)
					{
						size1++;
					}
					else
					{
						size2++;
					}
					windows[i].state=FREE;
					ischange=1;
					windows[i].resttime=0;				
				//	windows[i].restLen++;
					windows[i].rtime=0;
					windows[i].flag=0;							
				}//转换为“空闲”状态;
  				break;
		}
	}
}


