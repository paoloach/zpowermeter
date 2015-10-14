/**************************************************************************************************

 DESCRIPTION:
  --

 CREATED: 14/10/2015, by Paolo Achdjian

 FILE: CS2530.c

***************************************************************************************************/
#include "ZComDef.h"
#include "OSAL.h"
#include "ioCC2530.h"
#include "CS5463.h"


static byte CS5463TaskId;

extern void CS5463_Init( byte taskId ){
	CS5463TaskId = taskId;
}

/*
 *  Event Process for the task
 */
extern UINT16 CS5463_EventLoop( byte task_id, UINT16 events ) {
}
