struct clientData
{                         /*定义结构体*/
	                               
	char VIPID[6];
	char name[30];
	double balance;
};
typedef struct clientData CLIENT;
int enterChoice(void); 
void textFile(FILE *);                    
void updateRecord(FILE *);
void addRecord(FILE *);
void deleteRecord(FILE *);
int viptest(char [],FILE *);

