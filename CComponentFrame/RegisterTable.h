#ifndef _REGISTER_TABLE_H
#define _REGISTER_TABLE_H

#include"Sys_Configure.h"
#define MAX_REGISTER_TABLE 20
#define DECLARE_FUNC(funEntry) BOOL_STATUS funEntry##(void);
#define IMPLEMENT_FUNC(funName,funEntry) Sys_Rgs_Rgs(funName,funEntry);


typedef BOOL_STATUS(*funcEntryType)(void );


typedef struct  
{
	char name[MAX_RESERVED_WORD];
	funcEntryType fp;
}RegisterMap;

typedef struct 
{
	int num;
	RegisterMap registerMap[MAX_REGISTER_TABLE];
}RegisterTable;

//BOOL_STATUS Sys_LoadRgsTable(char filepath[]);

//BOOL_STATUS Sys_ParseRgsTable(int index,char name[], char func[]);

typedef enum{
	FuncSet = 0x01,
	FuncUnset = 0x10,
	EntrySet = 0x00,
}TableST;

/************************************************************************/
/* Register Process                                                                     */
/************************************************************************/
DECLARE_FUNC(XCCLProcess)
DECLARE_FUNC(JHCLProcess)
DECLARE_FUNC(CheckSigClosedProcess)
DECLARE_FUNC(JHProcess)




BOOL_STATUS Sys_Rgs_Rgs(char funName[],funcEntryType funEntry);


/************************************************************************/
/* Function Entry                                                                     */
/************************************************************************/



/************************************************************************/
/* Function  List                                                               */
/************************************************************************/


funcEntryType Sys_Rgs_getEnetry(char ch[]);
int Sys_Rgs_getNum(void);



#endif