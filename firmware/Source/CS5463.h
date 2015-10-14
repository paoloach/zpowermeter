/**************************************************************************************************

 DESCRIPTION:
  --

 CREATED: 14/10/2015, by Paolo Achdjian

 FILE: CS5463.h

***************************************************************************************************/
#ifndef __CS5463__H__
#define __CS5463__H__

/*
  * Initialization for the task
  */
extern void CS5463_Init( byte task_id );

/*
 *  Event Process for the task
 */
extern UINT16 CS5463_EventLoop( byte task_id, UINT16 events );

#endif