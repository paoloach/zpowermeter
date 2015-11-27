/**************************************************************************************************
  Filename:       PowerMeter_data.c
  Autorh: 		 Paolo Achdjia
  Created: 13/10/2015
**************************************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "ZComDef.h"
#include "OSAL.h"
#include "AF.h"
#include "ZDConfig.h"

#include "zcl.h"
#include "zcl_general.h"
#include "zcl_ha.h"

#include "PowerMeter.h"
#include "clusters/ClusterIdentify.h"
#include "clusters/ClusterBasic.h"
#include "clusters/ClusterPower.h"
#include "clusters/ClusterOnOff.h"

/*********************************************************************
 * CONSTANTS
 */

#define DEVICE_VERSION     0
#define FLAGS              0



/*********************************************************************
 * ATTRIBUTE DEFINITIONS - Uses REAL cluster IDs
 */

/*********************************************************************
 * SIMPLE DESCRIPTOR
 */
// This is the Cluster ID List and should be filled with Application specific cluster IDs.
#define ZCLON_OFF_MAX_INCLUSTERS       4
const cId_t onOff_InClusterList[ZCLON_OFF_MAX_INCLUSTERS] ={
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY,
  ZCL_CLUSTER_ID_GEN_POWER_CFG,
  ZCL_CLUSTER_ID_GEN_ON_OFF
};

#define ZCL_SMART_PLUG_MAX_INCLUSTERS       5
const cId_t smartplug_InClusterList[ZCL_SMART_PLUG_MAX_INCLUSTERS] ={
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY,
  ZCL_CLUSTER_ID_SE_SIMPLE_METERING,
  ZCL_CLUSTER_ID_GEN_ON_OFF,
  ZCL_CLUSTER_ID_HA_ELECTRICAL_MEASUREMENT,
};


#define ZCLON_OFF_MAX_OUTCLUSTERS       1
const cId_t onOff_OutClusterList[ZCLON_OFF_MAX_INCLUSTERS] ={
  ZCL_CLUSTER_ID_GEN_BASIC,
};

#define ZCL_SMART_PLUG_OUTCLUSTERS       2
const cId_t smartplug_OutClusterList[ZCL_SMART_PLUG_OUTCLUSTERS] ={
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY
};

SimpleDescriptionFormat_t OnOff_SimpleDesc = {
  ENDPOINT_ONOFF,                  			//  int Endpoint;
  ZCL_HA_PROFILE_ID,                	//  uint16 AppProfId[2];
  ZCL_HA_DEVICEID_ON_OFF_LIGHT,     	//  uint16 AppDeviceId[2];
  DEVICE_VERSION,           			//  int   AppDevVer:4;
  FLAGS,                    			//  int   AppFlags:4;
  ZCLON_OFF_MAX_INCLUSTERS,              //  byte  AppNumInClusters;
  (cId_t *)onOff_InClusterList, 	//  byte *pAppInClusterList;
  ZCLON_OFF_MAX_OUTCLUSTERS	,           //  byte  AppNumInClusters;
  (cId_t *)onOff_OutClusterList 	//  byte *pAppInClusterList;
};


SimpleDescriptionFormat_t PowerMetering_SimpleDesc = {
  ENDPOINT_METERING,                  			//  int Endpoint;
  ZCL_HA_PROFILE_ID,                	//  uint16 AppProfId[2];
  ZCL_HA_DEVICEID_SMART_PLUG  ,     	//  uint16 AppDeviceId[2];
  DEVICE_VERSION,           			//  int   AppDevVer:4;
  FLAGS,                    			//  int   AppFlags:4;
  ZCL_SMART_PLUG_MAX_INCLUSTERS,        //  byte  AppNumInClusters;
  (cId_t *)smartplug_InClusterList, 	//  byte *pAppInClusterList;
  ZCL_SMART_PLUG_OUTCLUSTERS,       //  byte  AppNumInClusters;
  (cId_t *)smartplug_OutClusterList 	//  byte *pAppInClusterList;
};


