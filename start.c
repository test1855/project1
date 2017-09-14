#include<stdio.h>
#include "egg.h"

void tietu1(void)
{
	int i,x,y;
	EggStart(1150,600);
	
	DrawBitmap("背景.bmp");
	OffsetPen(-1190,-100);
	DrawBitmap("vip窗口1.bmp");
	DrawBitmap("vip窗口2.bmp");
	DrawBitmap("普通窗口3.bmp");
	DrawBitmap("普通窗口4.bmp");
	DrawBitmap("普通窗口5.bmp");
	DrawBitmap("普通窗口6.bmp");
	DrawBitmap("普通窗口7.bmp");
	DrawBitmap("普通窗口8.bmp");
	OffsetPen(-1150,0);
	DrawBitmap("休息按钮.bmp");
	for(i=0;i<7;i++)
	{
	  OffsetPen(90,0);
	  DrawBitmap("休息按钮.bmp"); 
	}
	OffsetPen(-900,-200);
	x=GetPenXPos();
	y=GetPenYPos();
	printf("%lf,%lf",x,y);
	DrawBitmap("取号机.bmp");
	OffsetPen(150,0);
	DrawBitmap("营业员.bmp");
	
	OffsetPen(100,0);
	DrawBitmap("显示屏.bmp");
}


