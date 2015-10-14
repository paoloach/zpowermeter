/**************************************************************************************************
  Filename:       PowerMeter.h
  Revised:        $Date: 2015-10-13
 ************************************************************************************************/

#ifndef ZCL_SAMPLELIGHT_H
#define ZCL_SAMPLELIGHT_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "zcl.h"

/*********************************************************************
 * CONSTANTS
 */
#define ENDPOINT            13


/*********************************************************************
 * MACROS
 */
/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * VARIABLES
 */
extern SimpleDescriptionFormat_t powerMeter_SimpleDesc;

extern CONST zclAttrRec_t powerMeterAttrs[];

/*********************************************************************
 * FUNCTIONS
 */

 /*
  * Initialization for the task
  */
extern void powerMeter_Init( byte task_id );

/*
 *  Event Process for the task
 */
extern UINT16 powerMeterEventLoop( byte task_id, UINT16 events );


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* ZCL_SAMPLELIGHT_H */
