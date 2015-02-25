#include "FunctionTemplate.h"
#include <stdio.h>


FucntionTemplate g_functionTemplate;

BOOL_STATUS Sys_LoadTemplate(char filepath[])
{
	FILE *fp;
	char ch;
	char ch_buf[MAX_RESERVED_WORD];
	int ch_iter,path_iter,item_iter;
	PathST Pathstatus;
	ItemST Itemstatus;
	fp = fopen(filepath,"r");// read the Template file
	if(NULL == fp)
		return BOOL_FALSE;

	ch = fgetc(fp);
	ch_iter = 0;//ch counter
	path_iter = 0;//path counter
	item_iter = 0;//item counter
	while(ch != EOF)
	{
		if(ch != ' '&& ch!=':'&& ch!='\n')
		{
			ch_buf[ch_iter++]  =ch;
			if(ch_iter >= MAX_RESERVED_WORD)
			{
				fclose(fp);
				return BOOL_FALSE;
			}
			
		}else
		{
			if(ch_iter !=0)
			{
				ch_buf[ch_iter]='\0';
				ch_iter = 0;
				if(strcmp(ch_buf,"PATH") == 0)
				{
					if(Pathstatus == PATH || Itemstatus == ITEM)// syntax error
					{
						fclose(fp);
						return BOOL_FALSE;
					}
					Pathstatus = PATH;
					g_functionTemplate.length++;
				}else if(strcmp(ch_buf,"ITEM")== 0)
				{
					if(Pathstatus != PATH || Itemstatus == ITEM) //syntax error
					{
						fclose(fp);
						return BOOL_FALSE;
					}
					Itemstatus = ITEM;
				}else if(strcmp(ch_buf,"ENDPATH")==0)
				{	
					if(Pathstatus !=PATH || Itemstatus ==ITEM) //syntax error
					{
						fclose(fp);
						return BOOL_FALSE;
					}

					Pathstatus = PATH_CLEAR; 
					item_iter = 0;
					path_iter++;
				}
				else
				{
					if(Pathstatus == PATH) // already in PATH
					{
						if(Itemstatus == ITEM)// insert into item
						{
							g_functionTemplate.functionPths[path_iter].length++;
							strcpy(g_functionTemplate.functionPths[path_iter].functionBlock[item_iter],ch_buf);
							//			g_functionTemplate.functionPths[g_functionTemplate.length].functionBlock[g_functionTemplate.functionPths[g_functionTemplate.length].length]=ch_buf;
							item_iter++;
							Itemstatus = ITEM_CLEAR;

						}else //insert into Path name
						{
							
							strcpy(g_functionTemplate.functionPths[path_iter].name,ch_buf);
							
							if(g_functionTemplate.length>= MAX_FUNCTION_PATH)
							{
								fclose(fp);
								return BOOL_FALSE;
							}
							//			g_functionTemplate.functionPths[g_functionTemplate.length].name=ch_buf;//´æ´¢PATHÃû×Ö¡£
						}
					}
					else
					{
						fclose(fp);
						return BOOL_FALSE;
					}
				}
				memset(ch_buf,0,strlen(ch_buf));//clear the ch_buf;
			}
		}
		ch = fgetc(fp);
	}

	if(strcmp(ch_buf,"ENDPATH")==0)
		Pathstatus = PATH_CLEAR;

	if(Pathstatus!=PATH_CLEAR || Itemstatus!=ITEM_CLEAR)
	{
		fclose(fp);
		return BOOL_FALSE;
	}
	fclose(fp);
	return BOOL_TRUE;
}


BOOL_STATUS Sys_ParseTemplate()
{
	return BOOL_TRUE;
}

BOOL_STATUS Sys_getNextPath(char status[],char *pNextPath)// check and return the next Path
{
	int iterPath = 0;

	if(Sys_getNumOfPath() == 0)
		return BOOL_FALSE;

	if(strcmp(status,"begin")==0)
	{
		strcpy(pNextPath, g_functionTemplate.functionPths[0].name);
		return BOOL_TRUE;
	}

	while(iterPath < g_functionTemplate.length)
	{

		if(strcmp(g_functionTemplate.functionPths[iterPath].name,status)==0)
		{
			iterPath++;
			if(iterPath == g_functionTemplate.length)
			{
				strcpy(pNextPath , "return");
				return BOOL_FALSE;
			}
			else
			{
				strcpy(pNextPath, g_functionTemplate.functionPths[iterPath].name);
				return BOOL_TRUE;
			}
			
		}
		iterPath ++;
	}
	return BOOL_FALSE;
}

BOOL_STATUS Sys_getNextItem(char status[], char itemstatus[], char* pNextItem)
{
	int iterPath = 0;
	int iterItem = 0;
	int max_PathIter = Sys_getNumOfPath();
	int max_ItemIter = 0;

	while(iterPath < max_PathIter)
	{
		if(strcmp(g_functionTemplate.functionPths[iterPath].name,status)==0)//find the path
		{
			max_ItemIter = Sys_getNumOfItem(status);
			if(max_ItemIter == 0)
				return BOOL_FALSE;

			iterItem = 0;

			if(strcmp(itemstatus,"begin")==0)
			{
				strcpy(pNextItem, g_functionTemplate.functionPths[iterPath].functionBlock[0]);
				return BOOL_TRUE;
			}

			while(iterItem<max_ItemIter)
			{
				if(strcmp(g_functionTemplate.functionPths[iterPath].functionBlock[iterItem],itemstatus) == 0)//find the item
				{
					iterItem++;
					if(iterItem>=max_ItemIter)
						return BOOL_FALSE;

					strcpy(pNextItem, g_functionTemplate.functionPths[iterPath].functionBlock[iterItem]);
					return BOOL_TRUE;
				}
				iterItem ++;
			}
		}
		iterPath++;
	}
	return BOOL_FALSE;
}

int Sys_getNumOfPath()
{
	return g_functionTemplate.length;
}

int Sys_getNumOfItem(char status[])
{
	int iterPath = 0;
	while(iterPath < g_functionTemplate.length)
	{
		if(strcmp(g_functionTemplate.functionPths[iterPath].name,status)==0)
		{
			return g_functionTemplate.functionPths[iterPath].length;
		}
		iterPath++;
	}
	return -1;
}