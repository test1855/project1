#include<stdio.h>
#include<stdlib.h>
#include "egg.h"
#include "vipprotect.h"
#include "variable.h"

extern void opendoor(void)
{
	HEGG egg1,egg2;
	double x,y;
	int i=1;
	egg1=LayEgg();
	DrawBitmap("门左.bmp");
	egg2=LayEgg();
	MovePen(650,700);
	DrawBitmap("门右.bmp");
	
	while(!(WaitForEvent() == KEYDOWN)){}
	if(GetStruckKey() == VK_LBUTTON)
	{
		while(i<600)
		{
			SetActiveEgg(egg1);
			OffsetEgg(-1,0);
			
			SetActiveEgg(egg2);
			OffsetEgg(1,0);
			
			WaitFor(0.1);
			i++;	
		}								

	}
	SetActiveEgg(egg1);
	EatEgg(egg1);
	SetActiveEgg(egg2);
	EatEgg(egg2);	
} 


extern void closedoor(void)
{
	HEGG egg1,egg2;
	double x,y;
	int i=1;
	egg1=LayEgg();
	OffsetEgg(-650,0);
	DrawBitmap("门左关.bmp");
	egg2=LayEgg();
	OffsetEgg(1300,0);
	DrawBitmap("门右关.bmp");
	while(i<652)
	{
		SetActiveEgg(egg1);
		OffsetEgg(1,0);
			
		SetActiveEgg(egg2);
		OffsetEgg(-1,0);
			
		WaitFor(0.1);
		i++;	
	}								
	WaitForExit(); 
	SetActiveEgg(egg1);
	EatEgg(egg1);
	SetActiveEgg(egg2);
	EatEgg(egg2);	
} 

extern void queue(void)
{
	int i=0,j,h=0;
	LISTNODEPTR currentnormPtr=headp,currentvipPtr=headpVIP;
	MovePen(750,170);
	DrawString("normList:");
	while(currentnormPtr!=NULL)
	{
		DrawString(currentnormPtr->num);
		DrawString(" ->");
		i++;
		currentnormPtr=currentnormPtr->nextPtr;
		if(i==12)
			{
				MovePen(750,125);
			}
	} 
	if(i<=12)
		{
			for(j=1;j<=(60-5*i);j++)
				{
					DrawString("    ");
				}
			MovePen(750,125);
			for(j=1;j<=65;j++)
				{
					DrawString("    ");
				}
			MovePen(807,150);
			for(j=1;j<=i;j++)
				{
					DrawBitmap("顾客小.bmp");
					DrawString("    ");
				}
			for(j=1;j<=12-i;j++)
				{
					DrawBitmap("空白.bmp");	
					DrawString("    ");
				} 
			MovePen(745,105);
			for(j=1;j<=12;j++)
				{
					DrawBitmap("空白.bmp");	
					DrawString("    ");		
				}
		} 
	else
		{
			for(j=1;j<=(65-5*(i-12));j++)
				{
					DrawString("  ");
				}
			MovePen(807,150);
			for(j=1;j<=12;j++)
				{
					DrawBitmap("顾客小.bmp");
					DrawString("    ");
				}
			MovePen(745,105);
			for(j=1;j<=(i-12);j++)
				{
					DrawBitmap("顾客小.bmp");
					DrawString("    ");
				}
			for(j=1;j<=(25-i);j++)
				{
					DrawBitmap("空白.bmp");	
					DrawString("    ");	
				} 
		}
	MovePen(750,80);
	DrawString("vipList:");
	while(currentvipPtr!=NULL)
	{
		DrawString(currentvipPtr->num);
		DrawString("->");
		h++;
		currentvipPtr=currentvipPtr->nextPtr;
		if(h==12)
			{
				MovePen(750,35);
			}
	}
	if(h<=12)
		{
			for(j=1;j<=(60-5*h);j++)
				{
					DrawString("  ");
				}
			MovePen(750,35);
			for(j=1;j<=65;j++)
				{
					DrawString("  ");
				}
			MovePen(790,60);
			for(j=1;j<=h;j++)
				{
					DrawBitmap("顾客小.bmp");
					DrawString("    ");
				}
			for(j=1;j<=12-h;j++)
				{
					DrawBitmap("空白.bmp");	
					DrawString("    ");
				}
			MovePen(745,15);
			for(j=1;j<=12;j++)
				{
					DrawBitmap("空白.bmp");	
					DrawString("    ");		
				}
				
		}
	else
		{
			for(j=1;j<=(65-5*(h-12));j++)
				{
					DrawString("  ");
				}
			MovePen(790,60);
			for(j=1;j<=12;j++)
				{
					DrawBitmap("顾客小.bmp");
					DrawString("    ");
				}
			MovePen(745,15);
			for(j=1;j<=(h-12);j++)
				{
					DrawBitmap("顾客小.bmp");
					DrawString("    ");
				}
			for(j=1;j<=(25-h);j++)
				{
					DrawBitmap("空白.bmp");	
					DrawString("    ");	
				} 
		}
	
}



extern void tietu1(void)
{
	int i,x,y;
	EggStart(1300,700);
	DrawBitmap("哈哈哈新背景.bmp");
	MovePen(50,600);
	DrawBitmap("VIP1.bmp"); 
	DrawBitmap("VIP2.bmp");
	DrawBitmap("窗口1.bmp");
	DrawBitmap("窗口2.bmp"); 
	DrawBitmap("窗口3.bmp"); 
	DrawBitmap("窗口4.bmp"); 
	DrawBitmap("窗口5.bmp"); 
	DrawBitmap("窗口6.bmp"); 
    MovePen(200,700);
	DrawBitmap("标题.bmp");	
	MovePen(800,230);
	DrawBitmap("G.bmp");	
	MovePen(950,230);
	DrawBitmap("V.bmp");
	
	MovePen(1000,220);
	DrawBitmap("框框.bmp"); 
	
}

extern void eggstate_trans(void)
{
    int i,degree;
    char rtime[4],dtime[4],planrtime[4],plandtime[4];
    

	for(i=1;i<9;i++)
	{
     	MovePen((150*i-70),470);
     	DrawString("       ");
     	MovePen((150*i-70),470);
	    DrawString(windows[i-1].serveNo);
	    rtime[0]=(windows[i-1].rtime)/100+48;
	    rtime[1]=(windows[i-1].rtime%100)/10+48;
		rtime[2]=windows[i-1].rtime%10+48;
		rtime[3]='\0';
		planrtime[0]=(windows[i-1].planrtime)/100+48;
	    planrtime[1]=(windows[i-1].planrtime%100)/10+48;
		planrtime[2]=windows[i-1].planrtime%10+48;
		planrtime[3]='\0';
		dtime[0]=(windows[i-1].dtime)/100+48;
	    dtime[1]=(windows[i-1].dtime%100)/10+48;
		dtime[2]=windows[i-1].dtime%10+48;
		dtime[3]='\0';
		plandtime[0]=(windows[i-1].plandtime)/100+48;
	    plandtime[1]=(windows[i-1].plandtime%100)/10+48;
		plandtime[2]=windows[i-1].plandtime%10+48;
		plandtime[3]='\0';

	    MovePen(150*i-10,427);
	    DrawString(dtime);
	    DrawString("/");
	    DrawString(plandtime);
	    MovePen(150*i-10,400);
	    DrawString(rtime);
	    DrawString("/");
	    DrawString(planrtime);
	   
	    
		switch(windows[i-1].state)
   		{
   			case CLOSE://关闭 
   			    MovePen((150*i-70),500);
	            DrawString("       ");
				MovePen((150*i-70),500);
	            DrawString("CLOSE");
	            MovePen(150*i-50,300);
	            DrawBitmap("空白2.bmp"); 
   				break;
   			case FREE://空闲:
      			MovePen((150*i-70),500);
	            DrawString("            ");
				MovePen((150*i-70),500);
	            DrawString("FREE");
	            MovePen(150*i-50,300);
	            DrawBitmap("空白2.bmp"); 
  				break;
				
          	case WAIT://等待顾客：
              	MovePen((150*i-70),500);
	            DrawString("            ");
				MovePen((150*i-70),500);
	            DrawString("WAIT");
	            MovePen(150*i-50,300);
	            DrawBitmap("空白2.bmp"); 
              	break;
              	
          	case DEAL://办理中：
			   MovePen((150*i-70),500);
	            DrawString("            ");
				MovePen((150*i-70),500);
	            DrawString("DEAL");
	            MovePen(150*i-50,300);
	            DrawBitmap("顾客.bmp"); 
				break;
				
      		case FINISH://办理结束：
      		   MovePen((150*i-70),500);
	            DrawString("       ");
				MovePen((150*i-70),500);
	            DrawString("FINISH");
	            MovePen(150*i-50,300);
	            DrawBitmap("空白2.bmp"); 
      			break;
      			
	      	case PAUSE://暂停：
			MovePen((150*i-70),500);
	            DrawString("       ");
				MovePen((150*i-70),500);
	            DrawString("PAUSE");
	            MovePen(150*i-50,300);
	            DrawBitmap("空白2.bmp"); 
  				break;
  				
		}
	}
}

extern void getrest(void)
{
	double X,Y;
	if(GetStruckKey() == VK_LBUTTON)			//鼠标左键被按下
	{
		X=GetMouseX();
		Y=GetMouseY();
		if(((X>=115)&&(X<=140))&&((Y>=338)&&(Y<=363)))
	   	{
		   	addServListRest(1);
	   	}
		else if(((X>=265)&&(X<=290))&&((Y>=338)&&(Y<=363)))
	 	{
			addServListRest(2);    			  	
		}
		else if(((X>=415)&&(X<=440))&&((Y>=338)&&(Y<=363)))
		{
			addServListRest(3);
			    			
		}		
		else if(((X>=565)&&(X<=590))&&((Y>=338)&&(Y<=363)))
		{
		    addServListRest(4);
    	}
		else if(((X>=715)&&(X<=740))&&((Y>=338)&&(Y<=363)))
	    {		
	       addServListRest(5);
   	    }	
        else if(((X>=865)&&(X<=890))&&((Y>=338)&&(Y<=363)))
		{
	       addServListRest(6);	    			  		
		}
	    else if(((X>=1015)&&(X<=1040))&&((Y>=338)&&(Y<=363)))
    	{
           addServListRest(7);
	    }
     	else if(((X>=1165)&&(X<=1190))&&((Y>=338)&&(Y<=363)))			    
		{
	       addServListRest(8);
		}
			    
	}
}




