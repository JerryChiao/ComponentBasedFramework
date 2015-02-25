#include "Sys_Configure.h"
#include "Scheduler.h"
#include "FunctionTemplate.h"
#include "RegisterTable.h"
#include <stdlib.h>
#include <stdio.h>
//#include <unistd.h>

extern RegisterTable g_registerTable;
extern FucntionTemplate g_functionTemplate;
/************************************************************************/
/* function: to register the implemented function into the registertable;
Called at the first stage of the of the system*/
/************************************************************************/
BOOL_STATUS Sys_Initial()
{

	IMPLEMENT_FUNC("XCCL",&XCCLProcess)
	IMPLEMENT_FUNC("JHCL",&JHCLProcess)
	IMPLEMENT_FUNC("CKSIG_CLOSED",&CheckSigClosedProcess)
	IMPLEMENT_FUNC("JHMK",&JHProcess)
	return BOOL_TRUE;
}


// check the configuration file
BOOL_STATUS Sys_Check()
{
	char filepath[] ="Configuration.txt";
	char exePath[MAX_RESERVED_WORD];
	char exeName[MAX_RESERVED_WORD];
	char currName[MAX_RESERVED_WORD];
	char currPath[MAX_RESERVED_WORD];
	int flag = 0;
	int num_Tmp = 0;

	if(BOOL_FALSE==Sys_LoadTemplate(filepath))
	{
		return BOOL_FALSE;
	}
		
	num_Tmp=strcpy(currName,"begin");
	num_Tmp=strcpy(currPath,"begin");

	while(BOOL_TRUE == Sys_getNextPath(currPath,exePath))
	{
		while(BOOL_TRUE == Sys_getNextItem(exePath,currName,exeName))
		{
			if(Sys_Rgs_getEnetry(exeName)==0)
			{
				num_Tmp=printf(RED"Error: The function %  in % path is not registered! \n"NONE,exeName,exePath);
				flag = 1;
			}
			num_Tmp=strcpy(currName,exeName);
		}
		num_Tmp=strcpy(currPath,exePath);
	}
	
	if(flag)
		return BOOL_FALSE;

	return BOOL_TRUE;
}

BOOL_STATUS initial()
{
	return BOOL_FALSE;
}
void Sys_run()
{
	//int numPath = 0;
	//int numItem = 0;
	//int max_numPath = 0;
	int max_numItem = 0;
	char exePath[MAX_RESERVED_WORD];
	char exeName[MAX_RESERVED_WORD];
	char currName[MAX_RESERVED_WORD];
	char currPath[MAX_RESERVED_WORD];
	funcEntryType fp;
	int num_Tmp;
    //printf("\033[1;33m Hello World. \033[0m \n");
	num_Tmp=strcpy(currPath,"begin");
	while(BOOL_TRUE == Sys_getNextPath(currPath,exePath))
	{
		//strcpy(chPath,g_functionTemplate.functionPths[numPath].name);
		printf("***********************************\n");
		printf("Begin to execute the Path: %s\n",exePath);// begin to execute the path;

		max_numItem = Sys_getNumOfItem(exePath);
		printf("The number of the functions in the path is %d\n",max_numItem);
		num_Tmp=strcpy(currName,"begin");

		while(BOOL_TRUE == Sys_getNextItem(exePath,currName,exeName))
		{
			fp = Sys_Rgs_getEnetry(exeName);
			if( 0== fp)
			{
				num_Tmp=printf("Cannot find the entry point for : %s\n",exeName);
			}
			(*fp)();
			num_Tmp=strcpy(currName,exeName);
		}

		num_Tmp=strcpy(currPath,exePath);
	}
	//	max_numPath = Sys_getNumOfPath();//return the number of path
	/*while(numPath < max_numPath)
	{
		
		while(numItem < max_numItem)
		{
			strcpy(exeName,g_functionTemplate.functionPths[numPath].functionBlock[numItem]);
			
			fp = Sys_Rgs_getEnetry(exeName);
			if( 0== fp)
			{
				printf("Cannot find the entry point for : %s",exeName);
			}
			(*fp)();
			numItem ++;
		}
		numPath ++;
		numItem = 0;
	}
	*/
}



int main()
{
	int num_Tmp;

	char buf[2048];
	FILE *fp;
	char a;
	int i = 0;
	num_Tmp=printf("Test of Component Framework:\n");
	if(BOOL_FALSE == Sys_Initial())
	{
		num_Tmp=getchar();
		return -1;
	}

	if(BOOL_FALSE == Sys_Check())
	{
		num_Tmp=getchar();
		return -1;
	}
	fp = fopen("Configuration.txt","rb+");
	while(fread(&a,sizeof(char),1,fp)==1)
	{
		
		printf("%x\t%c\n",a,a);

	}

	//while(foef())
	//if(num_Tmp < 2048)
	//{
	//	while(i<num_Tmp)
	//	{
	//		printf("%x\n",buf+i*sizeof(char));
	//		i++;
	//	}
	//	printf("Read Completed!\n");

	//}

	num_Tmp=printf("Initialization Success!\n");

	Sys_run();
    printf("***********************************\n");
	num_Tmp=printf("Run Complete!\n");
	num_Tmp=printf("Input any key to stop the process: \n");
	num_Tmp=getchar();
	return 1;
}