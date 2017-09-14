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
extern LISTNODEPTR headp;         		extern LISTNODEPTR tailp;//指向普通客户队列头指针,尾指针
extern LISTNODEPTR headpVIP;      		extern LISTNODEPTR tailpVIP;//指向VIP客户队列头指针，尾指针 
extern WINTORESTPTR headpWinRest; 		extern WINTORESTPTR tailpWinRest;//指向窗口申请休息队列头指针，尾指针

extern EVENT_TYPE ev;

