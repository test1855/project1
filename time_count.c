#include<time.h>
void time_count(void)
{
	clock_t start, finish;
	double duration;/* 测量一个事件持续的时间*/
	start = clock();
	while(duration<1);//什么都不做
	{
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
	}	
}
