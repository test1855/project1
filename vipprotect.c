#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "vipprotect.h"



 void deleteRecord(FILE *cfPtr)
 {       
         int flag=0;                                /*ɾ��ĳһ������*/
         struct clientData VIPData,blankData={"","",0};
         char xnumber[6]; 
         printf("��������Ҫɾ����VIP�ͻ�ID��\n"); 
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
              printf("�ף��������ID��Ϣ��ɾ���������~"); 
              break;                                            
             }                 
         
		   }      
		   if(flag==0)
		  
		   printf("������˼��~��Ҫɾ����ID������~");             
          
          
          fclose(cfPtr);
       
		   
 }
void addRecord(FILE *cfPtr)
{
  
  struct clientData newData;
  printf("��~�밴vipid������������˳��������ӵ�VIP�ͻ���Ϣ���м��Կո������\n");
  scanf("%s %s %.2lf",newData.VIPID,newData.name,&newData.balance);
  fseek(cfPtr,0,SEEK_END);
  fwrite(&newData,sizeof(CLIENT),1,cfPtr);
  printf("�ף�ID��Ϣ����ӣ�ôô��~");
  fclose(cfPtr);
	
}
void updateRecord(FILE *cfPtr)
{                                       /*�ı�ĳһ������*/
     struct clientData VIPData,newData={"","",0};
     char xnumber[6];
    int flag=0;
     printf("��~��������Ҫ���µĿͻ�ID��\n"); 
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
	   printf("������˼�ף���Ҫ���µ�ID������~");	
	 		
	  }else if(flag==1){
	   	 printf("�밴vipid������������˳��������µ���Ϣ��\n");
         scanf("%s %s %.2lf",newData.VIPID,newData.name,&newData.balance);
	  	 fwrite(&newData,sizeof(CLIENT),1,cfPtr); 
	  	 printf("�ף�������µ�ID��Ϣ�Ѹ��£������~");
	  }
	  fclose(cfPtr);
          
}
       
int enterChoice(void)
{                                  /*�Բ˵���ʽչʾ*/
    int menuchoice;
    
    printf("\n��������ѡ��\n"
           "1--����VIP����\n"
           "2--����VIP����\n"
           "3--ɾ��VIP����\n"
           "4--��������ά���������ϼ�\n");
           fflush(stdin);
           scanf("%d",&menuchoice);
           
           return menuchoice;
     
    

    }
void textFile(FILE *cfPtr)
{                                    /*��ѧ����Ϣд���ļ�*/
	int n,i;
	struct clientData vipData={"","",0};    
	scanf("%d",&n);

		for(i=1;i<=n;i++)
		{                                                 /*ѭ�����ζ�ȡ��Ϣ*/
		 scanf("%s %s %.2lf",vipData.name,vipData.VIPID,&vipData.balance);
	     fwrite(&vipData,sizeof(CLIENT),1,cfPtr);
		}
		 fclose(cfPtr);
		 
	 
}
		


