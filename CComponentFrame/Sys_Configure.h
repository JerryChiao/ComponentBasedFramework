#ifndef _SYS_CONFIGURE_H
#define _SYS_CONFIGURE_H

#define MAX_FUNCTION_PATH 10
#define MAX_FUNCTION_ITEM 10
#define MAX_RESERVED_WORD 20


#define RED "\033[40;31m"
#define YELLOW "\033[40;33m"
#define NONE "\033[0m"


typedef enum
{
	BOOL_TRUE = 0x01,
	BOOL_FALSE=0x10,
}BOOL_STATUS;

/*structure to store a function path*/
typedef struct{
	int length;
	char name[MAX_RESERVED_WORD];
	char functionBlock[MAX_FUNCTION_ITEM][MAX_RESERVED_WORD];
} FunctionPath;


typedef struct{
	int length;//the number of the function Path
	FunctionPath functionPths[MAX_FUNCTION_PATH];
}FucntionTemplate;

typedef enum{	
	ITEM = 0x010,
	ITEM_CLEAR = 0x01,
}ItemST;


typedef enum{
	PATH = 0x011,
	PATH_CLEAR = 0x00,
}PathST;

/************************************************************************/
/* global variables;                                                                     */
/************************************************************************/
//extern FucntionTemplate g_functionTemplate;
//
//extern RegisterTable g_registerTable;

#endif


