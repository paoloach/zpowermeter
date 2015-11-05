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
	 /*
CONST zclAttrRec_t powerMeterAttrs[] = {
	POWER_ATTRIBUTES
	ONOF_ATTRIBUTES
 	LAST_CLUSTER_ATTRIBUTE
};*/

/*********************************************************************
 * SIMPLE DESCRIPTOR
 */
// This is the Cluster ID List and should be filled with Application specific cluster IDs.
#define ZCLSAMPLELIGHT_MAX_INCLUSTERS       4
const cId_t powerMeter_InClusterList[ZCLSAMPLELIGHT_MAX_INCLUSTERS] ={
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY,
  ZCL_CLUSTER_ID_GEN_POWER_CFG,
  ZCL_CLUSTER_ID_GEN_ON_OFF
};

#define ZCLSAMPLELIGHT_MAX_OUTCLUSTERS       1
const cId_t powerMeter_OutClusterList[ZCLSAMPLELIGHT_MAX_OUTCLUSTERS] ={
  ZCL_CLUSTER_ID_GEN_BASIC
};

SimpleDescriptionFormat_t OnOff_SimpleDesc = {
  ENDPOINT_ONOFF,                  			//  int Endpoint;
  ZCL_HA_PROFILE_ID,                	//  uint16 AppProfId[2];
  ZCL_HA_DEVICEID_ON_OFF_LIGHT,     	//  uint16 AppDeviceId[2];
  DEVICE_VERSION,           			//  int   AppDevVer:4;
  FLAGS,                    			//  int   AppFlags:4;
  ZCLSAMPLELIGHT_MAX_INCLUSTERS,        //  byte  AppNumInClusters;
  (cId_t *)powerMeter_InClusterList, 	//  byte *pAppInClusterList;
  ZCLSAMPLELIGHT_MAX_OUTCLUSTERS,       //  byte  AppNumInClusters;
  (cId_t *)powerMeter_OutClusterList 	//  byte *pAppInClusterList;
};



