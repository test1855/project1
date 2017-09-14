#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"egg.h"
#include "variable.h"
extern HANDLE hClientMutex;
/*函数功能：读取文件中的EVENT以后的字符，保存到theReqs的数组中，返回有效字符的总数*/			
static int get_fileInput(REQ theReqs[],FILE* sourcefPtr)
{
	int i=0,j=0;//i代表字符串数组的序号，j代表请求数组的序号 
	char ch[100]={};
	char vipid[100]={};
	int k=0,r=0;
	FILE *cfPtr;
	fscanf(sourcefPtr,"EVENT=%s\n",ch);	
	while(ch[i]!='\0')
	{
		switch(ch[i])
		{
			case 'Q':
				theReqs[j].resequence=0;
				theReqs[j].time=timeCount;
				i++;
				j++;
				break;
			case 'R':
				if(ch[i+1]=='1')
				{
					theReqs[j].resequence=1;
					theReqs[j].time=timeCount;
				}
				else if(ch[i+1]=='2')
				{
					theReqs[j].resequence=2;
					theReqs[j].time=timeCount;
				}
				else if(ch[i+1]=='3')
				{
					theReqs[j].resequence=3;
					theReqs[j].time=timeCount;
				}
				else if(ch[i+1]=='4')
				{
					theReqs[j].resequence=4;
					theReqs[j].time=timeCount;
				}
				else if(ch[i+1]=='5')
				{
					theReqs[j].resequence=5;
					theReqs[j].time=timeCount;
				}
				else if(ch[i+1]=='6')
				{
					theReqs[j].resequence=6;
					theReqs[j].time=timeCount;
				}
				else if(ch[i+1]=='7')
				{
					theReqs[j].resequence=7;
					theReqs[j].time=timeCount;
				}
				else if(ch[i+1]=='8')
				{
					theReqs[j].resequence=8;
					theReqs[j].time=timeCount;
				}
				i=i+2;
				j++;
				break;
			case 'G':
				theReqs[j].resequence=9;
				theReqs[j].time=timeCount; 
				i++;
				j++;
				break;		
			case 'V':
				if(ch[i+1]=='I'&&ch[i+2]=='D')
				{
					i=i+3;
					k=0;
                	while(ch[i]!='\0'&&ch[i]!='\n'&&ch[i]!='|')
                	{
                		vipid[k]=ch[i];
                		k++;
                		i++;
                	}
                	vipid[k]='\0';
                	if(k!=5)
                	{
                		r=0;
					}
					else 
					{
                		if((cfPtr=fopen("vip.txt","rb+"))==NULL)
                			printf("File could not open.\n");
                		else
                     	{
                            r=viptest(vipid,cfPtr);
                            fclose(cfPtr);
                     	}
                	}
                	
                 	if(r==1)  
					{
						theReqs[j].resequence=10;
					}                                            
					else
					{
						theReqs[j].resequence=9;	
					}
					theReqs[j].time=timeCount;
					j++;
				}
				break;
			case '|':
				i++;	
				break;
			case '\n':
				i++;
				break;
	/*		case '\0':
				break;  */				
		}
	}
	return j;
} 
/*函数功能：当读取到G字符时，分配普通客户号码，保存到普通客户排队的链表中*/ 
static void addServListCom(void)
{
	LISTNODEPTR newPtr;
	newPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
	if(newPtr!=NULL)
	{
		newPtr->num[0]=countG/100+48;  //分配普通客户号码 
		newPtr->num[1]=(countG/10)%10+48;
		newPtr->num[2]=countG%10+48;
		newPtr->num[3]='\0';
		newPtr->nextPtr=NULL;
		
		countG++;
		normServeLen++;
		
		if(headp==NULL)
		{
			headp=newPtr;
			tailp=newPtr;
			tailp->nextPtr=NULL;
		} 
		else
		{
			tailp->nextPtr=newPtr;
			tailp=newPtr;
			tailp->nextPtr=NULL;
		}
	}
}
/*函数功能：当读取到V字符时，分配普通VIP号码，保存到VIP客户排队的链表中*/ 


static void addServListVip(void)
{
	LISTNODEPTR newPtr;
	newPtr=(LISTNODEPTR)malloc(sizeof(LISTNODE));
	if(newPtr!=NULL)
	{
		newPtr->num[0]='V';
		newPtr->num[1]=countV/10+48;//分配VIP客户服务号码 
		newPtr->num[2]=countV%10+48;
		newPtr->num[3]='\0';
		newPtr->nextPtr=NULL;
		
		countV++;
		vipServeLen++;
		if((headpVIP)==NULL)
		{
			headpVIP=newPtr;
			tailpVIP=newPtr;
			tailpVIP->nextPtr=NULL;
		} 
		else
		{
			tailpVIP->nextPtr=newPtr;
			tailpVIP=newPtr;
			tailpVIP->nextPtr=NULL;
		}
	}
}

/*函数功能：当读取到休息窗口的请求时，保存到休息排队的链表中*/ 


extern void addServListRest(int number)
{
	WINTORESTPTR newPtr;
	newPtr=(WINTORESTPTR)malloc(sizeof(WINTOREST));
	if(newPtr!=NULL)
	{
		newPtr->t=timeCount;
		newPtr->restwin=number;
		newPtr->nextPtr=NULL;
		
		countR++;
		if(headpWinRest==NULL)
		{
			headpWinRest=newPtr;
			tailpWinRest=newPtr;
			tailpWinRest->nextPtr=NULL;
		} 
		else
		{
			tailpWinRest->nextPtr=newPtr;
			tailpWinRest=newPtr;
			tailpWinRest->nextPtr=NULL;
		}
	}
}

/*函数功能：（文件输入中）遍历theReqs，将不同的需求按要求分开，分别保存到三条链表中*/ 

extern int get_input(FILE* sourcefPtr)
{
	int size=0,i=0;
	REQ theReqs[100];
	
		size=get_fileInput(theReqs,sourcefPtr);
		for(i=0;i<size;i++)
		{
			printf("%d->",theReqs[i].resequence);
		}


			for(i=0;i<size&&close==0;i++)
			{
				switch(theReqs[i].resequence)
				{
					case 0:
						if(tailp!=NULL)
							tailp->nextPtr=NULL;
						if(tailpVIP!=NULL)
							tailpVIP->nextPtr=NULL;
						if(tailpWinRest!=NULL)
							tailpWinRest->nextPtr=NULL;
						close=1;//当读取到下班请求时，不在读取 
						break;
					case 1:
						addServListRest(theReqs[i].resequence);
						ischange=1;
						break;
					case 2:
						addServListRest(theReqs[i].resequence);
						ischange=1;
						break;
					case 3:
						addServListRest(theReqs[i].resequence);
						ischange=1;
						break;			
					case 4:
						addServListRest(theReqs[i].resequence);
						ischange=1;
						break;
					case 5:
						addServListRest(theReqs[i].resequence);
						ischange=1;
						break;
					case 6:
						addServListRest(theReqs[i].resequence);
						ischange=1;
						break;
					case 7:
						addServListRest(theReqs[i].resequence);
						ischange=1;
						break;
					case 8:
						addServListRest(theReqs[i].resequence); 
						ischange=1;
						break;
					case 9:
						addServListCom();
						ischange=1;
						break;
					case 10:
						addServListVip();
						ischange=1;
						break;
				}
			}
			return 1;
			
}
/*函数功能：键盘输入中，当读取到不同请求时，分别保存到不同链表中*/ 
extern DWORD WINAPI Fun1(LPVOID pPararneter)
{
	char st[15];
	int find=0;
	char vid[6];
	int i=0;
	int r=0;
	char vipid[6];
	FILE *cfPtr;
	while(1)
		{
			scanf("%s",st);
			WaitForSingleObject(hClientMutex,INFINITE); 
			if(strcmp(st,"G")==0)
				{
					addServListCom();
				}
			else if(strcmp(st,"Q")==0)
				{
					close=1;
					break;
				}
			else if(strcmp(st,"R1")==0)
				{
					addServListRest(1);	
				}
			else if(strcmp(st,"R2")==0)
				{
					addServListRest(2);	
				}
			else if(strcmp(st,"R3")==0)
				{
					addServListRest(3);	
				}
			else if(strcmp(st,"R4")==0)
				{
					addServListRest(4);	
				}
			else if(strcmp(st,"R5")==0)
				{
					addServListRest(5);	
				}
			else if(strcmp(st,"R6")==0)
				{
					addServListRest(6);	
				}
			else if(strcmp(st,"R7")==0)
				{
					addServListRest(7);	
				}
			else if(strcmp(st,"R8")==0)
				{
					addServListRest(8);	
				}
			else if(strcmp(st,"V")==0)   //VIP用户输入ID 
				{
					printf("亲，请输入您的ID~\n");
			        fflush(stdin);
			        scanf("%s",vipid);
		
			       	if((cfPtr=fopen("vip.txt","rb+"))==NULL)
	          			printf("File could not be opened.\n");
			      	else 
		         		{ 
		             		r=viptest(vipid,cfPtr);
		            		fclose(cfPtr);
		            		if(r==1) 
			              		addServListVip();
		               	 	else
		               			{ 
		                  			printf("亲，您的ID不存在，请重新输入~\n");
		                 			fflush(stdin);
			             			scanf("%s",vipid);
			              			if((cfPtr=fopen("vip.txt","rb+"))==NULL)
	                	       			printf("File could not be opened.\n");
	                      			else
	            	       			{
										r=viptest(vipid,cfPtr);
		                      			fclose(cfPtr);
			                 			if(r==1) 
			                   				addServListVip();
			                  			else
			                   			{
			                    			printf("亲，您的ID不存在，请重新输入~您还有最后一次机会~\n");
			                   		 		fflush(stdin);
			                    	    	scanf("%s",vipid);
                        					if((cfPtr=fopen("vip.txt","rb+"))==NULL) 
	                        					printf("File could not be opened.\n");
	                        				else
	                        				{
		                      					r=viptest(vipid,cfPtr);
		                      					fclose(cfPtr);
			                  					if(r==1) 
			                    					addServListVip();
			                  					else 
			                   					{
			    	             					printf("不好意思亲，您已用完三次机会，已为您按普通用户处理~\n");
			    	             					addServListCom();
			                   					}
			                				}
					     				}     
		            				} 
		         			 }
		          
						}	
				}
				else
				{
					printf("输入错误！请您重新输入\n");
				}
			
			timeCount++;
			ReleaseMutex(hClientMutex);																																
		}
}
extern void getNum(void)
{
	double X, Y;
	char l[4];						//用于得到鼠标按下时的横纵坐标
	char vid[50];
	FILE * vipPtr;
	int i=0,j=0,count=1,r=0;					//count为计数器输入ID共三次
	
	char spaceStrForInput[50];			//用于回显的空字符串
	

	for(j = 0; j < 50; ++j)				//初始化 
	{
		vid[j] = '\0';
		spaceStrForInput[j] = '\0';
	}
	/*得到刚好能够覆盖显示框的 空格	字符*/	
	for(j = 0; j < 50; ++j)	
	{
		spaceStrForInput[j] = ' ';
	}
	
//	while(1)
//	{
		i=0;j=0;count=1;r=0;
		MovePen(800,250);
		
//		if(ev==KEYDOWN)		
//	{	//while(!(WaitForEvent() == KEYDOWN)) {}//若未遇到 KEYDOWN事件（键盘输入或者鼠标点击），则什么都不做。
		if(GetStruckKey() == VK_LBUTTON)			//鼠标左键被按下
		{
			X = GetMouseX();
			Y = GetMouseY();
			if((X >=20 && X <= 320)&&(Y >=170 && Y <=250))   //加坐标！！！！！！！！！ 两个！！！！ 
			{
				strategy=1;//VIP定向服务 
				MovePen(50,250);
				DrawString("亲~您已选择VIP定向服务策略"); 
			}
			else if((X >=20 && X <= 320)&&(Y >=20 && Y <=100))  //加坐标！！！！！！！ 两个！！！！ 
			{
				strategy=2;//VIP顺便服务 
				MovePen(50,250);
				DrawString("亲~您已选择VIP顺便服务策略");
			}
			else if( ((X >= 1200)&&(X <= 1300))&&((Y >= 600) && (Y <= 700)) )
			{
				close=1;
			}
			else if((X >= 800 && X <= 850) && (Y >=180  && Y <= 230))			//G按钮被按下
			{
				addServListCom();
				MovePen(800,250);				
				DrawString("亲~为您分配的号码是");
				DrawString(tailp->num);
				l[0]=(normServeLen-1)/100+48;
				l[1]=((normServeLen-1)%100)/10+48;
				l[2]=(normServeLen-1)%10+48;
				l[3]='\0';
				DrawString("您前面等待的客户有");
				DrawString(l);
				DrawString("请您耐心等待哦"); 
			}
			else if((X >= 950 && X <= 1000) && (Y >= 180 && Y <=230))		//V按钮被按下
			{

					MovePen(1000,230);
					DrawString("亲~请输入您的ID~~"); 
					fflush(stdin);
					MovePen(1000,200);
					DrawString(spaceStrForInput);
					MovePen(1000,200);
					while(count<=3)
					{
						while(!(WaitForEvent() == KEYDOWN)) {}	  //若未遇到 KEYDOWN事件（键盘输入或者鼠标点击），则什么都不做。
						
						vid[i]=GetStruckKey();
						if(vid[i] == VK_LBUTTON) 
						{
							vid[i]='\0';
						} //若左键被按下，则什么都不做 
						else		//否则则是键盘输入 
		{
					//	vid[i]=GetStruckKey();
						while( vid[i] !=VK_RETURN )	
						{
							fflush(stdin);
							DrawString(&vid[i]);
							printf("%c",vid[i]);
							i++;
							while(!(WaitForEvent() == KEYDOWN)) {}
							if(GetStruckKey() == VK_LBUTTON) {}
							else 
							vid[i]=GetStruckKey();			
						}
						vid[i]='\0';
						i = 0;
						if((vipPtr=fopen("vip.txt","r+"))==NULL)
						{
							printf("ERROR");
						}
						else
						{						
							r=viptest(vid,vipPtr);
							fclose(vipPtr); 
							for(j = 0; j < 50; ++j) 
							{
								vid[j] = '\0';
							}
							if(r==1)
							{
								addServListVip();
								MovePen(800,250);			
								DrawString("亲~为您分配的号码是");
								DrawString(tailpVIP->num);
								l[0]=(vipServeLen-1)/100+48;
								l[1]=((vipServeLen-1)%100)/10+48;
								l[2]=(vipServeLen-1)%10+48;
								l[3]='\0';
								DrawString("您前面等待的客户有");
								DrawString(l);
								DrawString("请您耐心等待哦"); 
								MovePen(1000,230);
								DrawString(spaceStrForInput);
								MovePen(1000,200);
								DrawString(spaceStrForInput); 
								break;
							}
							else
							{
								if(count==3)
								{
									for(j=0;j<50;++j) vid[j]='\0'; 
									addServListCom();
									MovePen(800,250);			
									DrawString("亲~为您分配的号码是");
									DrawString(tailp->num);
									l[0]=(normServeLen-1)/100+48;
									l[1]=((normServeLen-1)%100)/10+48;
									l[2]=(normServeLen-1)%10+48;
									l[3]='\0';
									DrawString("您前面等待的客户有");
									DrawString(l);
									DrawString("请您耐心等待哦"); 
									MovePen(1000,230);
									DrawString(spaceStrForInput);
									MovePen(1000,200);
									DrawString(spaceStrForInput); 
								}
								else
								{
									MovePen(1000,230);
									DrawString("亲~输入有误哦~请重新输入"); 
									MovePen(1000,200);
									DrawString(spaceStrForInput);
									MovePen(1000,200);
								}									
								count++;
							}
		
						}
	//}
					}
			}
		}
	}
//}
}


