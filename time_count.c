#include<time.h>
void time_count(void)
{
	clock_t start, finish;
	double duration;/* ����һ���¼�������ʱ��*/
	start = clock();
	while(duration<1);//ʲô������
	{
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
	}	
}
