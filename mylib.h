#include<string.h>
enum EVENTTYPE{Q , R1 , R2 , R3 , R4 , R5 , R6 , R7 , R8 , G ,V};
enum STATE{CLOSE,FREE,WAIT,DEAL,FINISH,PAUSE};
struct listNode
{
	char num[4];
	struct listNode* nextPtr;
};//�ͻ��������������������ڽ�� 
typedef struct listNode LISTNODE;
typedef LISTNODE* LISTNODEPTR;

struct winToRest
{
	int t;
    int restwin;//��Ϣ����
    struct winToRest* nextPtr;
};//������Ϣ������н��
typedef struct winToRest WINTOREST;
typedef WINTOREST* WINTORESTPTR;
struct window 
{
    int number;//���ں�
	enum STATE state;//����״̬
	char serveNo[4];//��ǰ����ͻ��ĺ���
	int serveLen;//����ʱ��
	int perserveLen;//ƽ������ʱ��
	int wtime;//�ȴ�ʱ��
	int dtime;//����ʱ�� 
	int rtime;//��Ϣʱ�� 
	int dealtime;
	int resttime;
	int plandtime;
	int planrtime;
	int restLen;//��Ϣʱ��
	int custCount;//����ͻ�����
	int custnormCount;//������ͨ�ͻ�����
	int custvipCount;//����VIP�ͻ�����
	int custsatisfyGood;//�������
	int custsatisfyNorm;//��������
	int custsatisfyBad;//�������
	int flag; //0û����Ϣ����1����Ϣ���� 
};//������Ϣ��ģ
typedef struct window WINDOW;
struct Req
{
	int time;
	int resequence;//�����󻻻�int������ 
};
typedef struct Req REQ;



