
#include<stdio.h>
#include<string.h>
#include "vipprotect.h"

int viptest(char id[],FILE *cfPtr)

{
	int r=0;
	CLIENT VIPData;
	while(!feof(cfPtr))
	{
	  fread(&VIPData,sizeof(CLIENT),1,cfPtr); 

          if(strcmp(VIPData.VIPID,id)==0)
		  {
		    r=1;	
		    break;
		  	
		  }		
	}
    return r;	
}
