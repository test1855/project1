#include<stdio.h>
#include "egg.h"

void tietu1(void)
{
	int i,x,y;
	EggStart(1150,600);
	
	DrawBitmap("����.bmp");
	OffsetPen(-1190,-100);
	DrawBitmap("vip����1.bmp");
	DrawBitmap("vip����2.bmp");
	DrawBitmap("��ͨ����3.bmp");
	DrawBitmap("��ͨ����4.bmp");
	DrawBitmap("��ͨ����5.bmp");
	DrawBitmap("��ͨ����6.bmp");
	DrawBitmap("��ͨ����7.bmp");
	DrawBitmap("��ͨ����8.bmp");
	OffsetPen(-1150,0);
	DrawBitmap("��Ϣ��ť.bmp");
	for(i=0;i<7;i++)
	{
	  OffsetPen(90,0);
	  DrawBitmap("��Ϣ��ť.bmp"); 
	}
	OffsetPen(-900,-200);
	x=GetPenXPos();
	y=GetPenYPos();
	printf("%lf,%lf",x,y);
	DrawBitmap("ȡ�Ż�.bmp");
	OffsetPen(150,0);
	DrawBitmap("ӪҵԱ.bmp");
	
	OffsetPen(100,0);
	DrawBitmap("��ʾ��.bmp");
}


