/************************************************************************/
/* header file of Function template                                                                     */
/************************************************************************/

#ifndef _FUNCTION_TEMPLATE_H
#define _FUNCTION_TEMPLATE_H

#include "Sys_Configure.h"
/*load the function Template file in the file path and give it to predefined structure*/
BOOL_STATUS Sys_LoadTemplate(char filepath[]);

BOOL_STATUS Sys_ParseTemplate();//parse the template and store it into the memory;

BOOL_STATUS Sys_getNextPath(char status[],char *pNextPath);//if succeed,return the next status to pNextpath

BOOL_STATUS Sys_getNextItem(char status[], char itemstatus[], char* pNextItem);

int Sys_getNumOfPath();

int Sys_getNumOfItem(char status[]);//status is the current path id.



#endif