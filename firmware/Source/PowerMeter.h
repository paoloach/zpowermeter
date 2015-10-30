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

#include "zcl.h"

#define ENDPOINT_ONOFF            13
	
#define ENDPOINT_SMART_PLUG       15


extern SimpleDescriptionFormat_t OnOff_SimpleDesc;
extern SimpleDescriptionFormat_t SmartPlug_SimpleDesc;

extern CONST struct zclAttrRec_t onOffAttrs[];
extern CONST struct zclAttrRec_t smartPlugAttrs[];

extern void powerMeter_Init( byte task_id );

extern UINT16 powerMeterEventLoop( byte task_id, UINT16 events );



#ifdef __cplusplus
}
#endif

#endif /* ZCL_SAMPLELIGHT_H */
