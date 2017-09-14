#include<stdio.h>
#include<stdlib.h>
#include"variable.h"
#include<windows.h>
DWORD WINAPI Fun1(LPVOID pPararneter);
extern HANDLE hClientMutex;
void bank2(FILE* destfPtr,FILE* destfPtr1,FILE* destfPtr2)
{
	int readtime=0;
	HANDLE hThread1;
	hClientMutex=CreateMutex(NULL,FALSE,"print");
	hThread1=CreateThread(NULL,0,Fun1,NULL,0,NULL);  
	CloseHandle(hThread1);
	while(headp!=NULL||headpVIP!=NULL||close!=1||over!=1)
		{
		ischange=0;	
		WaitForSingleObject(hClientMutex,INFINITE); 
		control();
		state_trans();
		print1(destfPtr);
		if(ischange==1)
		{
			print2(destfPtr1);
		}
		timeCount++;
		ReleaseMutex(hClientMutex);
		Sleep(5000);
		}
	printStatistics(destfPtr2);
	printScreen3();
}
