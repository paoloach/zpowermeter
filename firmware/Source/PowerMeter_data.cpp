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
#include "clusters/ClusterMetering.h"
#include "clusters/ClusterElectricityMeasure.h"

/*********************************************************************
 * CONSTANTS
 */

#define DEVICE_VERSION     0
#define FLAGS              0



/*********************************************************************
 * ATTRIBUTE DEFINITIONS - Uses REAL cluster IDs
 */
CONST struct zclAttrRec_t onOffAttrs[] = {
	BASIC_ATTRIBUTE
	IDENTIFY_ATTRIBUTES
	POWER_ATTRIBUTES
	ONOF_ATTRIBUTES
 	LAST_CLUSTER_ATTRIBUTE
};

CONST struct zclAttrRec_t smartPlugAttrs[] = {
	BASIC_ATTRIBUTE
	IDENTIFY_ATTRIBUTES
	POWER_ATTRIBUTES
	ONOF_ATTRIBUTES
	METERING_ATTRIBUTES
	ELECTRICITY_MEASURE_ATTRIBUTES
 	LAST_CLUSTER_ATTRIBUTE
};

/*********************************************************************
 * SIMPLE DESCRIPTOR
 */
// This is the Cluster ID List and should be filled with Application specific cluster IDs.
#define ON_OFF_MAX_IN_CLUSTERS       4
const cId_t onOffInClusters[ON_OFF_MAX_IN_CLUSTERS] ={
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY,
  ZCL_CLUSTER_ID_GEN_POWER_CFG,
  ZCL_CLUSTER_ID_GEN_ON_OFF
};

#define SMART_PLUG_MAX_IN_CLUSTERS       6
const cId_t smartPlugInClusters[SMART_PLUG_MAX_IN_CLUSTERS] ={
  ZCL_CLUSTER_ID_GEN_BASIC,
  ZCL_CLUSTER_ID_GEN_IDENTIFY,
  ZCL_CLUSTER_ID_GEN_POWER_CFG,
  ZCL_CLUSTER_ID_SE_SIMPLE_METERING,
  ZCL_CLUSTER_ID_GEN_ON_OFF,
  ZCL_CLUSTER_ID_HA_ELECTRICAL_MEASUREMENT
};

#define ON_OFF_MAX_OUT_CLUSTERS       1
const cId_t onOffOutClusters[ON_OFF_MAX_OUT_CLUSTERS] ={
  ZCL_CLUSTER_ID_GEN_BASIC
};

#define SMART_PLUG_MAX_OUT_CLUSTERS       1
const cId_t smartPlugOutClusters[ON_OFF_MAX_OUT_CLUSTERS] ={
  ZCL_CLUSTER_ID_GEN_BASIC
};

SimpleDescriptionFormat_t OnOff_SimpleDesc = {
  ENDPOINT_ONOFF,                  	//  int Endpoint;
  ZCL_HA_PROFILE_ID,                //  uint16 AppProfId[2];
  ZCL_HA_DEVICEID_ON_OFF_LIGHT,     //  uint16 AppDeviceId[2];
  DEVICE_VERSION,           		//  int   AppDevVer:4;
  FLAGS,                    		//  int   AppFlags:4;
  ON_OFF_MAX_IN_CLUSTERS,        	//  byte  AppNumInClusters;
  (cId_t *)onOffInClusters, 		//  byte *pAppInClusterList;
  ON_OFF_MAX_OUT_CLUSTERS,       	//  byte  AppNumInClusters;
  (cId_t *)onOffOutClusters 		//  byte *pAppInClusterList;
};


SimpleDescriptionFormat_t SmartPlug_SimpleDesc = {
  ENDPOINT_SMART_PLUG,          		//  int Endpoint;
  ZCL_HA_PROFILE_ID,                	//  uint16 AppProfId[2];
  ZCL_HA_DEVICEID_SMART_PLUG,	     	//  uint16 AppDeviceId[2];
  DEVICE_VERSION,           			//  int   AppDevVer:4;
  FLAGS,                    			//  int   AppFlags:4;
  ON_OFF_MAX_IN_CLUSTERS,        		//  byte  AppNumInClusters;
  (cId_t *)smartPlugInClusters, 		//  byte *pAppInClusterList;
  ON_OFF_MAX_OUT_CLUSTERS,       		//  byte  AppNumInClusters;
  (cId_t *)smartPlugOutClusters		 	//  byte *pAppInClusterList;
};


