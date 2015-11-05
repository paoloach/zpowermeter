/**************************************************************************************************

 DESCRIPTION:
  --

 CREATED: 14/10/2015, by Paolo Achdjian

 FILE: PowerMeter.c

***************************************************************************************************/

#include "ZComDef.h"
#include "OSAL.h"
#include "AF.h"
#include "ZDApp.h"

#include "zcl.h"
#include "zcl_general.h"
#include "zcl_ha.h"
#include "PowerMeter.h"
#include "onboard.h"
/* HAL */
#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_key.h"
#include "zclReadAttributeFn.h"
#include "zclWriteAttributeFn.h"
#include "clusters/ClusterOSALEvents.h"
#include "clusters/ClusterIdentify.h"
#include "clusters/ClusterBasic.h"
#include "clusters/ClusterPower.h"
#include "clusters/ClusterOnOff.h"
#include "clusters/ClusterMetering.h"
#include "clusters/ClusterOnOff.h"
#include "clusters/ClusterElectricityMeasure.h"

static byte zPowerMeterTaskID;


static void zPowerMeter_ProcessIncomingMsg( zclIncomingMsg_t *msg );
static uint8 zPowerMeter_ProcessInReadRspCmd( zclIncomingMsg_t *pInMsg );
static uint8 zPowerMeter_ProcessInWriteRspCmd( zclIncomingMsg_t *pInMsg );
static uint8 zPowerMeter_ProcessInDefaultRspCmd( zclIncomingMsg_t *pInMsg );
#ifdef ZCL_DISCOVER
static uint8 zPowerMeter_ProcessInDiscRspCmd( zclIncomingMsg_t *pInMsg );
#endif
static ZStatus_t handleClusterCommands( zclIncoming_t *pInMsg );
/*********************************************************************
 * ZCL General Profile Callback table
 */
/*********************************************************************
 * @fn          temperatureHumiditySensor_Init
 *
 * @brief       Initialization function for the zclGeneral layer.
 *
 * @param       none
 *
 * @return      none
 */
void powerMeter_Init( byte task_id ){
	zPowerMeterTaskID = task_id;
	zclHA_Init( &OnOff_SimpleDesc );
	zcl_registerPlugin( ZCL_CLUSTER_ID_GEN_BASIC,  ZCL_CLUSTER_ID_GEN_MULTISTATE_VALUE_BASIC, handleClusterCommands );
 	
	addReadAttributeFn(ENDPOINT_ONOFF, ZCL_CLUSTER_ID_GEN_BASIC,basicClusterReadAttribute);
	addWriteAttributeFn(ENDPOINT_ONOFF, ZCL_CLUSTER_ID_GEN_BASIC,basicClusterWriteAttribute);
	addReadAttributeFn(ENDPOINT_ONOFF, ZCL_CLUSTER_ID_GEN_IDENTIFY,identifyClusterReadAttribute);
	addWriteAttributeFn(ENDPOINT_ONOFF, ZCL_CLUSTER_ID_GEN_IDENTIFY,identifyClusterWriteAttribute);
	addReadAttributeFn(ENDPOINT_ONOFF,ZCL_CLUSTER_ID_GEN_POWER_CFG,powerClusterReadAttribute);
	addReadAttributeFn(ENDPOINT_ONOFF, ZCL_CLUSTER_ID_GEN_ON_OFF,onOffClusterReadAttribute);
	addWriteAttributeFn(ENDPOINT_ONOFF, ZCL_CLUSTER_ID_GEN_ON_OFF,onOffClusterWriteAttribute);
	
	addReadAttributeFn(ENDPOINT_METERING, ZCL_CLUSTER_ID_GEN_BASIC,basicClusterReadAttribute);
	addWriteAttributeFn(ENDPOINT_METERING, ZCL_CLUSTER_ID_GEN_BASIC,basicClusterWriteAttribute);
	addReadAttributeFn(ENDPOINT_METERING, ZCL_CLUSTER_ID_GEN_IDENTIFY,identifyClusterReadAttribute);
	addWriteAttributeFn(ENDPOINT_METERING, ZCL_CLUSTER_ID_GEN_IDENTIFY,identifyClusterWriteAttribute);
	addReadAttributeFn(ENDPOINT_METERING,ZCL_CLUSTER_ID_GEN_POWER_CFG,powerClusterReadAttribute);
	addReadAttributeFn(ENDPOINT_METERING,ZCL_CLUSTER_ID_GEN_POWER_CFG,meteringClusterReadAttribute);
	addReadAttributeFn(ENDPOINT_METERING, ZCL_CLUSTER_ID_HA_ELECTRICAL_MEASUREMENT,electricityMeasureClusterReadAttribute);
	
	zcl_registerForMsg( zPowerMeterTaskID );
  
  	EA=1;
 	identifyInit(zPowerMeterTaskID);
	onOffInit();
}

/*********************************************************************
 * @fn          zclSample_event_loop
 *
 * @brief       Event Loop Processor for zclGeneral.
 *
 * @param       none
 *
 * @return      none
 */
uint16 powerMeterEventLoop( uint8 task_id, uint16 events ){
	afIncomingMSGPacket_t *MSGpkt;
  
	  (void)task_id;  // Intentionally unreferenced parameter
	 if ( events & SYS_EVENT_MSG ){
		while ( (MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive( zPowerMeterTaskID )) )  {
			switch ( MSGpkt->hdr.event ) {
				case ZCL_INCOMING_MSG:
          			// Incoming ZCL Foundation command/response messages
          			zPowerMeter_ProcessIncomingMsg( (zclIncomingMsg_t *)MSGpkt );
          			break;
		       default:
        		  break;
      		}

        osal_msg_deallocate( (uint8 *)MSGpkt );
    	}

    	return (events ^ SYS_EVENT_MSG);
	}
	
	if ( events & IDENTIFY_TIMEOUT_EVT ) {
		return identifyLoop(events);
	}
	
 	return 0;
}

/****************************************************************************** 
 * 
 *  Functions for processing ZCL Foundation incoming Command/Response messages
 *
 *****************************************************************************/

/*********************************************************************
 * @fn      zPowerMeter_ProcessIncomingMsg
 *
 * @brief   Process ZCL Foundation incoming message
 *
 * @param   pInMsg - pointer to the received message
 *
 * @return  none
 */
static void zPowerMeter_ProcessIncomingMsg( zclIncomingMsg_t *pInMsg){
	switch ( pInMsg->zclHdr.commandID ){
		case ZCL_CMD_READ_RSP:
			zPowerMeter_ProcessInReadRspCmd( pInMsg );
			break;
		case ZCL_CMD_WRITE_RSP:
			zPowerMeter_ProcessInWriteRspCmd( pInMsg );
			break;
#ifdef ZCL_REPORT
    // See ZCL Test Applicaiton (zcl_testapp.c) for sample code on Attribute Reporting
		case ZCL_CMD_CONFIG_REPORT:
      	//zclSampleLight_ProcessInConfigReportCmd( pInMsg );
			break;
    
		case ZCL_CMD_CONFIG_REPORT_RSP:
      //zclSampleLight_ProcessInConfigReportRspCmd( pInMsg );
			break;
    
		case ZCL_CMD_READ_REPORT_CFG:
      //zclSampleLight_ProcessInReadReportCfgCmd( pInMsg );
			break;
    
		case ZCL_CMD_READ_REPORT_CFG_RSP:
      //zclSampleLight_ProcessInReadReportCfgRspCmd( pInMsg );
			break;
    
		case ZCL_CMD_REPORT:
      	//zclSampleLight_ProcessInReportCmd( pInMsg );
			break;
#endif   
		case ZCL_CMD_DEFAULT_RSP:
			zPowerMeter_ProcessInDefaultRspCmd( pInMsg );
			break;
#ifdef ZCL_DISCOVER     
		case ZCL_CMD_DISCOVER_RSP:
			zPowerMeter_ProcessInDiscRspCmd( pInMsg );
			break;
#endif  
		default:
			break;
	}
  
	if ( pInMsg->attrCmd )
    	osal_mem_free( pInMsg->attrCmd );
}

/*********************************************************************
 * @fn      zPowerMeter_ProcessInReadRspCmd
 *
 * @brief   Process the "Profile" Read Response Command
 *
 * @param   pInMsg - incoming message to process
 *
 * @return  none
 */
static uint8 zPowerMeter_ProcessInReadRspCmd( zclIncomingMsg_t *pInMsg ){
	zclReadRspCmd_t *readRspCmd;
	uint8 i;

	readRspCmd = (zclReadRspCmd_t *)pInMsg->attrCmd;
	for (i = 0; i < readRspCmd->numAttr; i++){
		// Notify the originator of the results of the original read attributes attempt and, for each successfull request, the value of the requested attribute
	}

	return TRUE; 
}

/*********************************************************************
 * @fn      zPowerMeter_ProcessInWriteRspCmd
 *
 * @brief   Process the "Profile" Write Response Command
 *
 * @param   pInMsg - incoming message to process
 *
 * @return  none
 */
static uint8 zPowerMeter_ProcessInWriteRspCmd( zclIncomingMsg_t *pInMsg ){
 	zclWriteRspCmd_t *writeRspCmd;
 	uint8 i;

 	writeRspCmd = (zclWriteRspCmd_t *)pInMsg->attrCmd;
 	for (i = 0; i < writeRspCmd->numAttr; i++) {
		// Notify the device of the results of the its original write attributes command.
 	}

 	return TRUE; 
}

/*********************************************************************
 * @fn      zPowerMeter_ProcessInDefaultRspCmd
 *
 * @brief   Process the "Profile" Default Response Command
 *
 * @param   pInMsg - incoming message to process
 *
 * @return  none
 */
static uint8 zPowerMeter_ProcessInDefaultRspCmd( zclIncomingMsg_t *pInMsg ){
	// zclDefaultRspCmd_t *defaultRspCmd = (zclDefaultRspCmd_t *)pInMsg->attrCmd;
   
	// Device is notified of the Default Response command.
  	(void)pInMsg;
  
  	return TRUE; 
}

#ifdef ZCL_DISCOVER
/*********************************************************************
 * @fn      zPowerMeter_ProcessInDiscRspCmd
 *
 * @brief   Process the "Profile" Discover Response Command
 *
 * @param   pInMsg - incoming message to process
 *
 * @return  none
 */
static uint8 zPowerMeter_ProcessInDiscRspCmd( zclIncomingMsg_t *pInMsg ){
	zclDiscoverRspCmd_t *discoverRspCmd;
 	uint8 i;
  
 	discoverRspCmd = (zclDiscoverRspCmd_t *)pInMsg->attrCmd;
  	for ( i = 0; i < discoverRspCmd->numAttr; i++ ) {
		// Device is notified of the result of its attribute discovery command.
  	}
  
 	return TRUE;
}
#endif // ZCL_DISCOVER

/*********************************************************************
 * @brief      dispatch the cluster command to the right callback function
 *
 * @param   pInMsg - incoming message to process
 *
 * @return  none
 */
static ZStatus_t handleClusterCommands( zclIncoming_t *pInMsg ){
	ZStatus_t stat = ZFailure;

	if (zcl_ServerCmd( pInMsg->hdr.fc.direction ) ) {
		switch ( pInMsg->msg->clusterId ){
		    case ZCL_CLUSTER_ID_GEN_BASIC:
    		return processBasicClusterCommands(pInMsg);
	    case ZCL_CLUSTER_ID_GEN_IDENTIFY:
			return processIdentifyClusterServerCommands( pInMsg );
	    case ZCL_CLUSTER_ID_GEN_GROUPS:
    	case ZCL_CLUSTER_ID_GEN_SCENES:
	    case ZCL_CLUSTER_ID_GEN_ON_OFF:
    	case ZCL_CLUSTER_ID_GEN_LEVEL_CONTROL:
	    case ZCL_CLUSTER_ID_GEN_ALARMS:
    	case ZCL_CLUSTER_ID_GEN_LOCATION:
	    case ZCL_CLUSTER_ID_GEN_POWER_CFG:
    	case ZCL_CLUSTER_ID_GEN_DEVICE_TEMP_CONFIG:
	    case ZCL_CLUSTER_ID_GEN_ON_OFF_SWITCH_CONFIG:
    	case ZCL_CLUSTER_ID_GEN_TIME:
	    default:
    	  stat = ZFailure;
	      break;
  		}
	} else {
		switch ( pInMsg->msg->clusterId ){
	
  	    case ZCL_CLUSTER_ID_GEN_IDENTIFY:
			return processIdentifyClusterClientCommands( pInMsg );
	    default:
    	  stat = ZFailure;
	      break;
  		}
	}

  return ( stat );
}



/****************************************************************************
****************************************************************************/


