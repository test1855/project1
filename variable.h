#include "mylib.h"
#include "egg.h"

extern int MaxSeqLen1,MinSec1,MaxSec1,MinRestSec1,MaxRestSec1,VIPSERVLen1,WaitTime1;
extern int countG,countV,countR;
extern int normServeLen,vipServeLen;
extern int size1,size2;
extern int timeCount;
extern int ischange,close,over;
extern int strategy;
extern WINDOW windows[8];
extern LISTNODEPTR headp;         		extern LISTNODEPTR tailp;//ָ����ͨ�ͻ�����ͷָ��,βָ��
extern LISTNODEPTR headpVIP;      		extern LISTNODEPTR tailpVIP;//ָ��VIP�ͻ�����ͷָ�룬βָ�� 
extern WINTORESTPTR headpWinRest; 		extern WINTORESTPTR tailpWinRest;//ָ�򴰿�������Ϣ����ͷָ�룬βָ��

extern EVENT_TYPE ev;

