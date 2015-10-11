/**************************************************************************************************

 DESCRIPTION:
  Metering Cluster

 CREATED: 08/09/2015, by Paolo Achdjian

 FILE: ClusterMetering.h

***************************************************************************************************/

#ifndef __CLUSTER_METERING__H__
#define __CLUSTER_METERING__H__

#include "zcl_general.h"
#include "zcl.h"
#include "ClusterOSALEvents.h"
#include "uint48.h"


#define ATTRID_METERING_CURRENT_SUMMATION_DELIVERED 0

extern uint48 currentSummationDelivered;
extern uint8  status;
extern uint8  unitOfMeasure;
extern uint8  summationFormatting;
extern uint8  metteringDeviceType;


#define POWER_ATTRIBUTES  \
	{ ZCL_CLUSTER_ID_SE_SIMPLE_METERING, {  ATTRID_METERING_CURRENT_SUMMATION_DELIVERED,  ZCL_DATATYPE_UINT48, ACCESS_CONTROL_READ, (void *)&currentSummationDelivered, NULL  }  },  \
	{ ZCL_CLUSTER_ID_SE_SIMPLE_METERING, {  ATTRID_POWER_CFG_BATTERY_VOLTAGE,  ZCL_DATATYPE_UINT8, ACCESS_CONTROL_READ, (void *)&batteryVoltage, NULL  }  },  \
	{ ZCL_CLUSTER_ID_SE_SIMPLE_METERING, {  ATTRID_POWER_CFG_BAT_ALARM_MASK,  ZCL_DATATYPE_BITMAP8, ACCESS_CONTROL_READ, (void *)&batteryAlarmMask, NULL  }  },
	

#endif