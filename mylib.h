#include<string.h>
enum EVENTTYPE{Q , R1 , R2 , R3 , R4 , R5 , R6 , R7 , R8 , G ,V};
enum STATE{CLOSE,FREE,WAIT,DEAL,FINISH,PAUSE};
struct listNode
{
	char num[4];
	struct listNode* nextPtr;
};//客户到来队列请求队列链表节结点 
typedef struct listNode LISTNODE;
typedef LISTNODE* LISTNODEPTR;

struct winToRest
{
	int t;
    int restwin;//休息窗口
    struct winToRest* nextPtr;
};//窗口休息请求队列结点
typedef struct winToRest WINTOREST;
typedef WINTOREST* WINTORESTPTR;
struct window 
{
    int number;//窗口号
	enum STATE state;//窗口状态
	char serveNo[4];//当前服务客户的号码
	int serveLen;//服务时长
	int perserveLen;//平均服务时长
	int wtime;//等待时间
	int dtime;//办理时间 
	int rtime;//休息时间 
	int dealtime;
	int resttime;
	int plandtime;
	int planrtime;
	int restLen;//休息时长
	int custCount;//服务客户人数
	int custnormCount;//服务普通客户人数
	int custvipCount;//服务VIP客户人数
	int custsatisfyGood;//服务好评
	int custsatisfyNorm;//服务中评
	int custsatisfyBad;//服务差评
	int flag; //0没有休息请求，1有休息请求 
};//窗口信息建模
typedef struct window WINDOW;
struct Req
{
	int time;
	int resequence;//把请求换回int类型了 
};
typedef struct Req REQ;



