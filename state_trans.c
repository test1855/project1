#include<stdio.h>
#include<time.h>
#include"variable.h"
extern int MaxSeqLen1,MinSec1,MaxSec1,MinRestSec1,MaxRestSec1,VIPSERVLen1,WaitTime1;
extern void state_trans(void)//WINDOW windows[],int size,......)��ͨ�ͻ� 
{
    int i,degree;
    int arrival,sign,stop;
	for(i=0;i<8;i++)
	{
		switch(windows[i].state)
   		{
   			case CLOSE://�ر� 
   				if(i>1&&close==0&&normServeLen>=3*size1)//��̬����ͨ���� 
   				{
   					windows[i].state=FREE;
   					ischange=1;
   					size1++;
				}
				else if(i<=1&&close==0&&vipServeLen>=3)//��̬��vip���� 
				{
					windows[i].state=FREE;
					ischange=1;
					size2++;
				}
   				break;
   			case FREE://����:
      			if(strcmp(windows[i].serveNo,"   ")!=0)//�ӵ�����)
  				{
  					windows[i].state=WAIT;//״̬�л������ȴ��˿͡�;
  					ischange=1;
                    windows[i].wtime++;//�����ȴ���ʱ;          
       			}
                else if((windows[i].flag==1)&&(i>1)&&(size1>3))//����Ϣ����������ͨ��)
  				{	
                  	windows[i].state=PAUSE;//״̬�л�������ͣ��;
                  	ischange=1;
                  	size1--;
                  	srand(time(NULL));
                  	stop=MinRestSec1+rand()%(MaxRestSec1-MinRestSec1+1);
                  	windows[i].resttime=stop;
                  	windows[i].planrtime=stop;
					windows[i].rtime++;//������Ϣ��ʱ;
					windows[i].restLen++;
              	}
              	else if((windows[i].flag==1)&&(i<=1)&&(size2==2))//����Ϣ����������ͨ��)
  				{	
                  	windows[i].state=PAUSE;//״̬�л�������ͣ��;
                  	ischange=1;
                  	size2--;
                  	srand(time(NULL));
                  	stop=MinRestSec1+rand()%(MaxRestSec1-MinRestSec1+1);
                  	windows[i].resttime=stop;
                  	windows[i].planrtime=stop;
					windows[i].rtime++;//������Ϣ��ʱ;
					windows[i].restLen++;
              	}
              	else if((i==size1+1)&&(close==0)&&(normServeLen<3*size1)&&(size1>3))//��̬�رն������ͨ���� 
				{
					windows[i].state=CLOSE;
					ischange=1;
					size1--;
				}
				else if((i>1)&&(close==1)&&(headp==NULL))//�°��رմ��� 
				{
					windows[i].state=CLOSE;
					ischange=1;
					size1--;
				}
				else if((i==size2-1)&&(close==0)&&(vipServeLen<3)&&(size2==2))//�رն����vip���� 
				{
					windows[i].state=CLOSE;
					ischange=1;
					size2--;
				}
				else if((i<=1)&&(close==1)&&(headpVIP==NULL))//�°��ر�vip���� 
				{
					windows[i].state=CLOSE;
					ischange=1;
					size2--;
				}
              	break;
          	  	case WAIT://�ȴ��˿ͣ�
              	srand(time(NULL));
              	arrival=rand()%2;//�����ģ��˿��Ƿ�����
	          	if(arrival==0&&windows[i].wtime<WaitTime1)//�˿�δ�����ҵȴ�δ��ʱ)
                {
                	windows[i].wtime++;
                } //do nothing
              	else if(arrival==0&&windows[i].wtime>=WaitTime1)//�˿�δ�����ҵȴ�ʱ�䵽)
                {
                	windows[i].wtime=0;
                	windows[i].state=FREE;
                	ischange=1;
                	strcpy(windows[i].serveNo,"   ");
                	
                } //תΪ������"״̬;......
              	else if(arrival==1&&windows[i].wtime<WaitTime1)//�˿͵����ҵȴ�ʱ��δ��ʱ)
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
         			srand(time(NULL));                             //��ʼ��һ�� 
          			sign=MinSec1+rand()%(MaxSec1-MinSec1+1); 
          			windows[i].dealtime=sign;
          			windows[i].plandtime=windows[i].plandtime+sign;			//������һ�� 
                } //תΪ�������С�״̬;���������ʱ;......
			  	break;
          	case DEAL://�����У�
				if(windows[i].dtime<windows[i].dealtime)//δ�ﵽ�ƻ�����ʱ�� 
				{
					windows[i].serveLen++;
					windows[i].dtime++;
				}//donothing
				else if(windows[i].dtime>=windows[i].dealtime)		//��ʼ��һ��   
				{
				//	windows[i].serveLen++
               		windows[i].dtime=0;
               		windows[i].dealtime=0;
	               	windows[i].state=FINISH;
					ischange=1;	
	           		strcpy(windows[i].serveNo,"   ");	  
       			}//ת��Ϊ�����������״̬;
	       		break;
      		case FINISH://���������
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
				if((strcmp(windows[i].serveNo,"   "))!=0)//�ӵ�����)
    			{
			    	windows[i].state=WAIT;
			    	ischange=1;
			    }//ת��Ϊ���ȴ��˿͡�״̬;
			    else if(windows[i].flag==1)
			    {
			    	windows[i].state=PAUSE;//״̬�л�������ͣ��;
                  	ischange=1;
                  	size1--;
                  	srand(time(NULL));
					stop=MinRestSec1+rand()%(MaxRestSec1-MinRestSec1+1);
                  	windows[i].resttime=stop;
                  	windows[i].planrtime=stop;
					windows[i].rtime++;//������Ϣ��ʱ;	
              		windows[i].restLen++;
				}//����Ϣ����ת��Ϊ��ͣ״̬ */
 				else//������
   				{
			    	windows[i].state=FREE;
			    	ischange=1;
			    }//ת��Ϊ�����С�״̬;
      			break;
	      	case PAUSE://��ͣ��
				if(windows[i].rtime<windows[i].resttime)
				{
					windows[i].rtime++;
					windows[i].restLen++;  //��һ�� 
				}
				else if((windows[i].rtime)>=(windows[i].resttime))   //��ʼ��һ�� 
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
				}//ת��Ϊ�����С�״̬;
  				break;
		}
	}
}


