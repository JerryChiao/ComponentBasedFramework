#include "Sys_Configure.h"
#include "RegisterTable.h"
#include <stdio.h>

//RegisterTable g_registerTable[]=
//{
//	"XCCL",XXCLProcess,
//	"JHCL",JHCLProcess,
//	"CKSIG_CLOSED",CheckSigClosedProcess,
//	"JHMK",JHProcess,
//	"null",
//};

RegisterTable g_registerTable;
extern FucntionTemplate g_functionTemplate;
//RegisterTable g_registerTable[MAX_REGISTER_TABLE];

funcEntryType Sys_Rgs_getEnetry(char chr[])
{
	int iterTable = 0;
	int iterMax = Sys_Rgs_getNum();
	while(iterTable < iterMax)
	{
		if(strcmp(g_registerTable.registerMap[iterTable].name,chr)==0)
		{

			return g_registerTable.registerMap[iterTable].fp;
		}
		iterTable++;
	}
	return NULL;
}
/*

BOOL_STATUS Sys_LoadRgsTable(char filepath[])
{
	FILE *fp;
	char ch;
	char ch_buf[MAX_RESERVED_WORD];
	char ch_Func[MAX_RESERVED_WORD];
	char ch_Entry[MAX_RESERVED_WORD];
	int ch_conter=0;
	TableST tst=FuncUnset;
	fp =fopen(filepath,"r");

	ch = fgetc(fp);
	while(ch !=EOF)
	{
		if(ch!=' '&& ch!='\n')
		{
			ch_buf[ch_conter++] = ch;
		}
		else
		{
			if(ch =='\n')
			{
				if(tst ==FuncUnset)
					return BOOL_FALSE;
				strcpy(ch_Entry,ch_buf);
				memset(ch_buf,0,strlen(ch_buf));
				tst = EntrySet;

			}else
			{
				if(tst == FuncUnset)
				{
					strcpy(ch_Func,ch_buf);
					memset(ch_buf,0,strlen(ch_buf));
					tst = FuncSet;
				}
			}
		}
	}

	if(tst == FuncSet )
	{
		strcpy(ch_Entry,ch_buf);
		memset(ch_buf,0,strlen(ch_buf));
		return BOOL_TRUE;
	}else
	{
		return BOOL_FALSE;
	}

}
*/

BOOL_STATUS Sys_ParseRgsTable(int index,char name[], char func[])
{
	
	return BOOL_FALSE;
}

int Sys_Rgs_getNum(void)
{
	return g_registerTable.num;
}

BOOL_STATUS Sys_Rgs_Rgs(char funName[],funcEntryType funEntry)
{
	int index =0;
	if(g_registerTable.num >= MAX_REGISTER_TABLE)
		return BOOL_FALSE;
	
	for(index = 0; index <g_registerTable.num;index++)
	{
		if(strcmp(g_registerTable.registerMap[index].name,funName) == 0)
		{
			return BOOL_FALSE;
		}
	}

	g_registerTable.num++;
	index = g_registerTable.num-1;

	strcpy(g_registerTable.registerMap[index].name,funName);//copy the function
	g_registerTable.registerMap[index].fp = funEntry;
	return BOOL_TRUE;

}
