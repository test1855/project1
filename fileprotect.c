#include<stdio.h>
#include<string.h> 
extern int MaxSeqLen1,MinSec1,MaxSec1,MinRestSec1,MaxRestSec1,VIPSERVLen1,WaitTime1;
enum item{MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,WaitTime}; 
struct information
{
	char st[15];
	int num;
};
void fileWrite(void)
{  
	FILE *readPtr,*writePtr;
	struct information inf;
	int i=0;
	if((writePtr=fopen("配置文件.dat","w+b"))==NULL||(readPtr=fopen("配置文件1.txt","r"))==NULL)
		printf("File could not be opened.\n");
	else
		{
			while(!feof(readPtr)&&i<=6)
				{
					fscanf(readPtr,"%s%d",inf.st,&inf.num);
					fseek(writePtr,(i)*sizeof(struct information),SEEK_SET);
					fwrite(&inf,sizeof(struct information),1,writePtr);
					i++;
				}
			fclose(readPtr);
			fclose(writePtr);
		}		 
}

void fileUpdate(void)
{
	FILE *cPtr;
	struct information inf;
	int n;
	if((cPtr=fopen("配置文件.dat","r+b"))==NULL)
		printf("File could not be opened.\n");
	else
		{
			printf("请输入您想要修改的项目\n1--单队列最大允许等待长度(MaxSeqLen)\n"
					"2--单业务办理最短时长(MinSec)\n3--单业务办理最长时长(MaxSec)\n4--窗口休息最短时长(MinRestSec)\n5--窗口休息最长时长(MaxRestSec)\n"
					"6--VIP服务时长(VIPSERVLen)\n7--等待顾客到来时间长度(WaitTime)\n8--退出\n");
			scanf("%d",&n);
			while(n!=8)
			{
			printf("请您输入要修改的数字:\n");
			scanf("%d",&inf.num);
			if(n==1)
		    	{
					strcpy(inf.st,"MaxSeqLen");
					fseek(cPtr,(MaxSeqLen)*sizeof(struct information),SEEK_SET);
					fwrite(&inf,sizeof(struct information),1,cPtr);
				}
			else if(n==2)
				{
					strcpy(inf.st,"MinSec");
					fseek(cPtr,(MinSec)*sizeof(struct information),SEEK_SET);
					fwrite(&inf,sizeof(struct information),1,cPtr);
				}
			else if(n==3)
				{
					strcpy(inf.st,"MaxSec");
					fseek(cPtr,(MaxSec)*sizeof(struct information),SEEK_SET);
					fwrite(&inf,sizeof(struct information),1,cPtr);
				}
			else if(n==4)
				{
					strcpy(inf.st,"MinRestSec");
					fseek(cPtr,(MinRestSec)*sizeof(struct information),SEEK_SET);
					fwrite(&inf,sizeof(struct information),1,cPtr);
				}
			else if(n==5)
				{
					strcpy(inf.st,"MaxRestSec");
					fseek(cPtr,(MaxRestSec)*sizeof(struct information),SEEK_SET);
					fwrite(&inf,sizeof(struct information),1,cPtr);
				}			
			else if(n==6)
				{
					strcpy(inf.st,"VIPSERVLen");
					fseek(cPtr,(VIPSERVLen)*sizeof(struct information),SEEK_SET);
					fwrite(&inf,sizeof(struct information),1,cPtr);
				}
			else if(n==7)
				{
					strcpy(inf.st,"WaitTime");
					fseek(cPtr,(WaitTime)*sizeof(struct information),SEEK_SET);
					fwrite(&inf,sizeof(struct information),1,cPtr);
				}
			printf("请输入您想要修改的项目\n1--单队列最大允许等待长度(MaxSeqLen)\n"
					"2--单业务办理最短时长(MinSec)\n3--单业务办理最长时长(MaxSec)\n4--窗口休息最短时长(MinRestSec)\n5--窗口休息最长时长(MaxRestSec)\n"
					"6--VIP服务时长(VIPSERVLen)\n7--等待顾客到来时间长度(WaitTime)\n8--退出\n");
			scanf("%d",&n);
			}
			fclose(cPtr);
		}		
}
	
	
void fileRead(void)
{
	FILE *cPtr;
	struct information inf;
	int i;
	if((cPtr=fopen("配置文件.dat","rb"))==NULL)
		printf("File could not be opened.\n");
	else
		{
			for(i=MaxSeqLen;i<=WaitTime;i++)
				{
					switch(i)
						{
							case MaxSeqLen:
								fseek(cPtr,(MaxSeqLen)*sizeof(struct information),SEEK_SET);
								fread(&inf,sizeof(struct information),1,cPtr);
								MaxSeqLen1=inf.num;
								break;
							case MinSec:
								fseek(cPtr,(MinSec)*sizeof(struct information),SEEK_SET);
								fread(&inf,sizeof(struct information),1,cPtr);
								MinSec1=inf.num;
								break;
							case MaxSec:
								fseek(cPtr,(MaxSec)*sizeof(struct information),SEEK_SET);
								fread(&inf,sizeof(struct information),1,cPtr);
								MaxSec1=inf.num;
								break;
							case MinRestSec:
								fseek(cPtr,(MinRestSec)*sizeof(struct information),SEEK_SET);
								fread(&inf,sizeof(struct information),1,cPtr);
								MinRestSec1=inf.num;
								break;
							case MaxRestSec:
								fseek(cPtr,(MaxRestSec)*sizeof(struct information),SEEK_SET);
								fread(&inf,sizeof(struct information),1,cPtr);
								MaxRestSec1=inf.num;
								break;
							case VIPSERVLen:
								fseek(cPtr,(VIPSERVLen)*sizeof(struct information),SEEK_SET);
								fread(&inf,sizeof(struct information),1,cPtr);
								VIPSERVLen1=inf.num;
								break;
							case WaitTime:
								fseek(cPtr,(WaitTime)*sizeof(struct information),SEEK_SET);
								fread(&inf,sizeof(struct information),1,cPtr);
								WaitTime1=inf.num;
								break;
						}
				}
			fclose(cPtr);
		}
}	

void printInitial(void)
{
	FILE *showPtr,*fPtr;
	struct information inf;
	int i=0;
	if((showPtr=fopen("配置文件.txt","w"))==NULL||(fPtr=fopen("配置文件.dat","rb"))==NULL)
		printf("File could not be opened.\n");
	else
		{
			rewind(fPtr);
			while(!feof(fPtr)&&i<=6)
				{
					fseek(fPtr,(i)*sizeof(struct information),SEEK_SET);
					fread(&inf,sizeof(struct information),1,fPtr);
					fprintf(showPtr,"%s  %d\n",inf.st,inf.num);
					i++;
				}
			fclose(showPtr);
			fclose(fPtr);
		}
}	


