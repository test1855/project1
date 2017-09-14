#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "vipprotect.h"



 void deleteRecord(FILE *cfPtr)
 {       
         int flag=0;                                /*删除某一条数据*/
         struct clientData VIPData,blankData={"","",0};
         char xnumber[6]; 
         printf("输入您想要删除的VIP客户ID：\n"); 
         fflush(stdin);
         scanf("%s",xnumber);
       fseek(cfPtr,0,SEEK_SET);
		
            while(!feof(cfPtr))
		   { 
              fread(&VIPData,sizeof(CLIENT),1,cfPtr); 
              if(strcmp(VIPData.VIPID,xnumber)==0)
		     {
		  	  flag=1;
              fseek(cfPtr,(-1)*sizeof(CLIENT),SEEK_CUR);
              fwrite(&blankData,sizeof(CLIENT),1,cfPtr); 
              printf("亲，您输入的ID信息已删除，请放心~"); 
              break;                                            
             }                 
         
		   }      
		   if(flag==0)
		  
		   printf("不好意思亲~您要删除的ID不存在~");             
          
          
          fclose(cfPtr);
       
		   
 }
void addRecord(FILE *cfPtr)
{
  
  struct clientData newData;
  printf("亲~请按vipid、姓名、余额的顺序输入添加的VIP客户信息，中间以空格隔开；\n");
  scanf("%s %s %.2lf",newData.VIPID,newData.name,&newData.balance);
  fseek(cfPtr,0,SEEK_END);
  fwrite(&newData,sizeof(CLIENT),1,cfPtr);
  printf("亲，ID信息已添加，么么哒~");
  fclose(cfPtr);
	
}
void updateRecord(FILE *cfPtr)
{                                       /*改变某一条数据*/
     struct clientData VIPData,newData={"","",0};
     char xnumber[6];
    int flag=0;
     printf("亲~请输入想要更新的客户ID：\n"); 
     scanf("%s",xnumber);
     
     while(!feof(cfPtr))
	 {
          fread(&VIPData,sizeof(CLIENT),1,cfPtr); 
          if(strcmp(VIPData.VIPID,xnumber)==0)
		  {
		  	flag=1;
            fseek(cfPtr,(-1)*sizeof(CLIENT),SEEK_CUR);                                       
            break;                                            
          }                 
                            
     } 
	 if(flag==0)
	 {
	   printf("不好意思亲，您要更新的ID不存在~");	
	 		
	  }else if(flag==1){
	   	 printf("请按vipid、姓名、余额的顺序输入更新的信息：\n");
         scanf("%s %s %.2lf",newData.VIPID,newData.name,&newData.balance);
	  	 fwrite(&newData,sizeof(CLIENT),1,cfPtr); 
	  	 printf("亲，您想更新的ID信息已更新，请放心~");
	  }
	  fclose(cfPtr);
          
}
       
int enterChoice(void)
{                                  /*以菜单形式展示*/
    int menuchoice;
    
    printf("\n输入您的选择\n"
           "1--更新VIP资料\n"
           "2--增加VIP资料\n"
           "3--删除VIP资料\n"
           "4--结束资料维护，返回上级\n");
           fflush(stdin);
           scanf("%d",&menuchoice);
           
           return menuchoice;
     
    

    }
void textFile(FILE *cfPtr)
{                                    /*将学生信息写入文件*/
	int n,i;
	struct clientData vipData={"","",0};    
	scanf("%d",&n);

		for(i=1;i<=n;i++)
		{                                                 /*循环依次读取信息*/
		 scanf("%s %s %.2lf",vipData.name,vipData.VIPID,&vipData.balance);
	     fwrite(&vipData,sizeof(CLIENT),1,cfPtr);
		}
		 fclose(cfPtr);
		 
	 
}
		


