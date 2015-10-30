/**************************************************************************************************
  Filename:       zcl.h
  Revised:        $Date: 2014-06-25 18:07:01 -0700 (Wed, 25 Jun 2014) $
  Revision:       $Revision: 39221 $

  Description:    This file contains the Zigbee Cluster Library Foundation definitions.


  Copyright 2006-2014 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

#ifndef ZCL_H
#define ZCL_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "OSAL.h"
#include "OSAL_Nv.h"
#include "OSAL_Tasks.h"

#include "AF.h"
#include "aps_groups.h"
#include "zclListAttribute.h"
#include "zcl_clusterDef.h"
#include "hal_types.h"
	
#include "AttributeUtils.h"
#include "zclReadCmd_t.h"
#include "zclParseCmd.h"
#include "ZclWriteRspCmd.h"
#include "ZclWriteCmd.h"	
#include "ZCL_StatusCode.h"
	 
typedef unsigned short  uint16;

/*********************************************************************
 * CONSTANTS
 */
/*** Frame Control bit mask ***/
#define ZCL_FRAME_CONTROL_TYPE                          0x03
#define ZCL_FRAME_CONTROL_MANU_SPECIFIC                 0x04
#define ZCL_FRAME_CONTROL_DIRECTION                     0x08
#define ZCL_FRAME_CONTROL_DISABLE_DEFAULT_RSP           0x10

/*** Frame Types ***/
#define ZCL_FRAME_TYPE_PROFILE_CMD                      0x00
#define ZCL_FRAME_TYPE_SPECIFIC_CMD                     0x01

/*** Frame Client/Server Directions ***/
#define ZCL_FRAME_CLIENT_SERVER_DIR                     0x00
#define ZCL_FRAME_SERVER_CLIENT_DIR                     0x01

/*** Chipcon Manufacturer Code ***/
#define CC_MANUFACTURER_CODE                            0x1001

/*** Foundation Command IDs ***/
#define ZCL_CMD_READ                                    0x00
#define ZCL_CMD_READ_RSP                                0x01
#define ZCL_CMD_WRITE                                   0x02
#define ZCL_CMD_WRITE_UNDIVIDED                         0x03
#define ZCL_CMD_WRITE_RSP                               0x04
#define ZCL_CMD_WRITE_NO_RSP                            0x05
#define ZCL_CMD_CONFIG_REPORT                           0x06
#define ZCL_CMD_CONFIG_REPORT_RSP                       0x07
#define ZCL_CMD_READ_REPORT_CFG                         0x08
#define ZCL_CMD_READ_REPORT_CFG_RSP                     0x09
#define ZCL_CMD_REPORT                                  0x0a
#define ZCL_CMD_DEFAULT_RSP                             0x0b
#define ZCL_CMD_DISCOVER_ATTRS                          0x0c
#define ZCL_CMD_DISCOVER_ATTRS_RSP                      0x0d
#define ZCL_CMD_DISCOVER_CMDS_RECEIVED                  0x11
#define ZCL_CMD_DISCOVER_CMDS_RECEIVED_RSP              0x12
#define ZCL_CMD_DISCOVER_CMDS_GEN                       0x13
#define ZCL_CMD_DISCOVER_CMDS_GEN_RSP                   0x14
#define ZCL_CMD_DISCOVER_ATTRS_EXT                      0x15
#define ZCL_CMD_DISCOVER_ATTRS_EXT_RSP                  0x16

#define ZCL_CMD_MAX           ZCL_CMD_DISCOVER_ATTRS_EXT_RSP

// define reporting constant
#define ZCL_REPORTING_OFF     0xFFFF  // turn off reporting (maxReportInt)

// define command direction flag masks
#define CMD_DIR_SERVER_GENERATED          0x01
#define CMD_DIR_CLIENT_GENERATED          0x02
#define CMD_DIR_SERVER_RECEIVED           0x04
#define CMD_DIR_CLIENT_RECEIVED           0x08




/*** Attribute Access Control - bit masks ***/
#define ACCESS_CONTROL_READ                             0x01  // attribute can be read
#define ACCESS_CONTROL_WRITE                            0x02  // attribute can be written
#define ACCESS_CONTROL_R_W                              0x03  // attribute can be written
#define ACCESS_REPORTABLE                               0x04  // indicate attribute is reportable
#define ACCESS_CONTROL_COMMAND                          0x08
#define ACCESS_CONTROL_AUTH_READ                        0x10
#define ACCESS_CONTROL_AUTH_WRITE                       0x20
#define ACCESS_CLIENT                                   0x80  // TI unique, indicate client side attribute

// Access Control as reported OTA via DiscoveryAttributesExtended
#define ACCESS_CONTROLEXT_MASK                          0x07  // read/write/reportable bits same as above

#define ZCL_ATTR_ID_MAX                                 0xFFFF

// Used by Configure Reporting Command
#define ZCL_SEND_ATTR_REPORTS                           0x00
#define ZCL_EXPECT_ATTR_REPORTS                         0x01

// Predefined Maximum String Length
#define MAX_UTF8_STRING_LEN                             50

// Used by zclReadWriteCB_t callback function
#define ZCL_OPER_LEN                                    0x00 // Get length of attribute value to be read
#define ZCL_OPER_READ                                   0x01 // Read attribute value
#define ZCL_OPER_WRITE                                  0x02 // Write new attribute value

/*********************************************************************
 * MACROS
 */
#define zcl_ProfileCmd( a )         ( (a) == ZCL_FRAME_TYPE_PROFILE_CMD )
#define zcl_ClusterCmd( a )         ( (a) == ZCL_FRAME_TYPE_SPECIFIC_CMD )

#define zcl_ServerCmd( a )          ( (a) == ZCL_FRAME_CLIENT_SERVER_DIR )
#define zcl_ClientCmd( a )          ( (a) == ZCL_FRAME_SERVER_CLIENT_DIR )

#define UNICAST_MSG( msg )          ( (msg)->wasBroadcast == false && (msg)->groupId == 0 )

// Padding needed if buffer has odd number of octects in length
#define PADDING_NEEDED( bufLen )    ( (bufLen) % 2 )

// Check for Cluster IDs
#define ZCL_CLUSTER_ID_GEN( id )      ( /* (id) >= ZCL_CLUSTER_ID_GEN_BASIC &&*/ \
                                        (id) <= ZCL_CLUSTER_ID_GEN_COMMISSIONING )
#define ZCL_CLUSTER_ID_CLOSURES( id ) ( (id) >= ZCL_CLUSTER_ID_CLOSURES_SHADE_CONFIG && \
                                        (id) <= ZCL_CLUSTER_ID_CLOSURES_WINDOW_COVERING )
#define ZCL_CLUSTER_ID_HVAC( id )     ( (id) >= ZCL_CLUSTER_ID_HVAC_PUMP_CONFIG_CONTROL && \
                                        (id) <= ZCL_CLUSTER_ID_HVAC_USER_INTERFACE_CONFIG )
#define ZCL_CLUSTER_ID_LIGHTING( id ) ( (id) >= ZCL_CLUSTER_ID_LIGHTING_COLOR_CONTROL && \
                                        (id) <= ZCL_CLUSTER_ID_LIGHTING_BALLAST_CONFIG )
#define ZCL_CLUSTER_ID_MS( id )       ( (id) >= ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT && \
                                        (id) <= ZCL_CLUSTER_ID_MS_OCCUPANCY_SENSING )
#define ZCL_CLUSTER_ID_SS( id )       ( (id) >= ZCL_CLUSTER_ID_SS_IAS_ZONE && \
                                        (id) <= ZCL_CLUSTER_ID_SS_IAS_WD )
#define ZCL_CLUSTER_ID_KEY( id )      ( (id) == ZCL_CLUSTER_ID_GEN_KEY_ESTABLISHMENT )
#define ZCL_CLUSTER_ID_SE( id )       ( (id) >= ZCL_CLUSTER_ID_SE_PRICING && \
                                        (id) <= ZCL_CLUSTER_ID_SE_MDU_PAIRING )
#define ZCL_CLUSTER_ID_PI( id )       ( (id) >= ZCL_CLUSTER_ID_PI_GENERIC_TUNNEL && \
                                        (id) <= ZCL_CLUSTER_ID_PI_11073_PROTOCOL_TUNNEL )
#define ZCL_CLUSTER_ID_LL( id )       ( (id) == ZCL_CLUSTER_ID_LIGHT_LINK )
#define ZCL_CLUSTER_ID_PART( id )     ( (id) == ZCL_CLUSTER_ID_GEN_PARTITION )

#define ZCL_CLUSTER_ID_PC( id )       ( (id) == ZCL_CLUSTER_ID_GEN_POLL_CONTROL )

#define ZCL_CLUSTER_ID_EM( id )	      ( (id) == ZCL_CLUSTER_ID_HA_ELECTRICAL_MEASUREMENT )

#define ZCL_CLUSTER_ID_DIAG( id )     ( (id) == ZCL_CLUSTER_ID_HA_DIAGNOSTIC )

#define ZCL_CLUSTER_ID_MI( id )       ( (id) == ZCL_CLUSTER_ID_HA_METER_IDENTIFICATION )

#define ZCL_CLUSTER_ID_APPL_C( id )   ( (id) == ZCL_CLUSTER_ID_GEN_APPLIANCE_CONTROL )

#define ZCL_CLUSTER_ID_APPL_I( id )   ( (id) == ZCL_CLUSTER_ID_HA_APPLIANCE_IDENTIFICATION )

#define ZCL_CLUSTER_ID_APPL_STAT( id ) ( (id) == ZCL_CLUSTER_ID_HA_APPLIANCE_STATISTICS )

#define ZCL_CLUSTER_ID_APPL_E_A( id ) ( (id) == ZCL_CLUSTER_ID_HA_APPLIANCE_EVENTS_ALERTS )

#define ZCL_CLUSTER_ID_APPL_S( id )   ( (id) == ZCL_CLUSTER_ID_HA_APPLIANCE_STATISTICS )

#define ZCL_CLUSTER_ID_PP( id )       ( (id) == ZCL_CLUSTER_ID_GEN_POWER_PROFILE )

#define ZCL_CLUSTER_ID_DL( id )       ( (id) == ZCL_CLUSTER_ID_CLOSURES_DOOR_LOCK )

#define LAST_CLUSTER_ATTRIBUTE { ACHDJIAN_LAST_CLUSTER, {  0,  0, 0,  NULL  } } 

/*********************************************************************
 * TYPEDEFS
 */
// zcl_ProcessMessageMSG() return codes
typedef enum
{
  ZCL_PROC_SUCCESS = 0,                 // Message was processed
  ZCL_PROC_INVALID ,                    // Format or parameter was wrong
  ZCL_PROC_EP_NOT_FOUND,                // Endpoint descriptor not found
  ZCL_PROC_NOT_OPERATIONAL,             // Can't respond to this command
  ZCL_PROC_INTERPAN_FOUNDATION_CMD,     // INTER-PAN and Foundation Command (not allowed)
  ZCL_PROC_NOT_SECURE,                  // Security was required but the message is not secure
  ZCL_PROC_MANUFACTURER_SPECIFIC,       // Manufacturer Specific command - not handled
  ZCL_PROC_MANUFACTURER_SPECIFIC_DR,    // Manufacturer Specific command - not handled, but default response sent
  ZCL_PROC_NOT_HANDLED,                 // No default response was sent and the message was not handled
  ZCL_PROC_NOT_HANDLED_DR,              // default response was sent and the message was not handled
} zclProcMsgStatus_t;

// ZCL header - frame control field
typedef struct
{
  unsigned int type:2;
  unsigned int manuSpecific:1;
  unsigned int direction:1;
  unsigned int disableDefaultRsp:1;
  unsigned int reserved:3;
} zclFrameControl_t;

// ZCL header
typedef struct
{
  zclFrameControl_t fc;
  uint16            manuCode;
  uint8             transSeqNum;
  uint8             commandID;
} zclFrameHdr_t;


// Configure Reporting Command format
typedef struct
{
  uint8  direction;          // to send or receive reports of the attribute
  uint16 attrID;             // attribute ID
  uint8  dataType;           // attribute data type
  uint16 minReportInt;       // minimum reporting interval
  uint16 maxReportInt;       // maximum reporting interval, 0xFFFF=off
  uint16 timeoutPeriod;      // timeout period
  uint8  *reportableChange;  // reportable change (only applicable to analog data type)
                             // - the size depends on the attribute data type
} zclCfgReportRec_t;

typedef struct
{
  uint8             numAttr;    // number of attribute IDs in the list
  zclCfgReportRec_t attrList[1]; // attribute ID list
} zclCfgReportCmd_t;

// Attribute Status record
typedef struct
{
  uint8  status;             // should be ZCL_STATUS_SUCCESS or error
  uint8  direction;          // whether attributes are reported or reports of attributes are received
  uint16 attrID;             // attribute ID
} zclCfgReportStatus_t;

// Configure Reporting Response Command format
typedef struct
{
  uint8                numAttr;    // number of attribute status in the list
  zclCfgReportStatus_t attrList[1]; // attribute status records
} zclCfgReportRspCmd_t;

// Read Reporting Configuration Command format
typedef struct
{
  uint8  direction; // to send or receive reports of the attribute
  uint16 attrID;    // attribute ID
} zclReadReportCfgRec_t;

typedef struct
{
  uint8                 numAttr;    // number of attributes in the list
  zclReadReportCfgRec_t attrList[1]; // attribute ID list
} zclReadReportCfgCmd_t;

// Attribute Reporting Configuration record
typedef struct
{
  uint8  status;             // status field
  uint8  direction;          // to send or receive reports of the attribute
  uint16 attrID;             // attribute ID
  uint8  dataType;           // attribute data type
  uint16 minReportInt;       // minimum reporting interval
  uint16 maxReportInt;       // maximum reporting interval
  uint16 timeoutPeriod;      // timeout period
  uint8  *reportableChange;  // reportable change (only applicable to analog data type)
                             // - the size depends on the attribute data type
} zclReportCfgRspRec_t;

// Read Reporting Configuration Response Command format
typedef struct
{
  uint8                numAttr;    // number of records in the list
  zclReportCfgRspRec_t attrList[1]; // attribute reporting configuration list
} zclReadReportCfgRspCmd_t;

// Attribute Report
typedef struct
{
  uint16 attrID;             // atrribute ID
  uint8  dataType;           // attribute data type
  uint8  *attrData;          // this structure is allocated, so the data is HERE
                             // - the size depends on the data type of attrID
} zclReport_t;

// Report Attributes Command format
typedef struct
{
  uint8       numAttr;       // number of reports in the list
  zclReport_t attrList[1];    // attribute report list
} zclReportCmd_t;

// Default Response Command format
typedef struct
{
  uint8  commandID;
  uint8  statusCode;
} zclDefaultRspCmd_t;

// Discover Attributes and Attributes Extended Command format
typedef struct
{
  uint16 startAttr;          // specifies the minimum value of the identifier
                             // to begin attribute discovery.
  uint8  maxAttrIDs;         // maximum number of attribute IDs that are to be
                             // returned in the resulting response command.
} zclDiscoverAttrsCmd_t;

// Attribute Report info
typedef struct
{
  uint16 attrID;             // attribute ID
  uint8  dataType;           // attribute data type (see Table 17 in Spec)
} zclDiscoverAttrInfo_t;

// Discover Attributes Response Command format
typedef struct
{
  uint8             discComplete; // whether or not there're more attributes to be discovered
  uint8             numAttr;      // number of attributes in the list
  zclDiscoverAttrInfo_t attrList[1];   // supported attributes list
} zclDiscoverAttrsRspCmd_t;

// String Data Type
typedef struct
{
  uint8 strLen;
  uint8 *pStr;
} UTF8String_t;

// Command format for the following:
// Discover Commands Received, Discover Commands Generated
typedef struct
{
  uint8 startCmdID;
  uint8 maxCmdID;
} zclDiscoverCmdsCmd_t;

// Command format for the following:
// Discover Commands Received Response Command, Discover Commands Generated Response
typedef struct
{
  uint8 discComplete;
  uint8 cmdType;    // either ZCL_CMD_DISCOVER_CMDS_GEN or ZCL_CMD_DISCOVER_CMDS_RECEIVED
  uint8 numCmd;     // number of provided commands
  uint8 *pCmdID;    // variable length array
} zclDiscoverCmdsCmdRsp_t;

// Discover Attributes Extended Response Command format
typedef struct
{
  uint16 attrID;
  uint8 attrDataType;
  uint8 attrAccessControl;
} zclExtAttrInfo_t;

typedef struct
{
  uint8 discComplete;
  uint8 numAttr;                  // number of attributes provided
  zclExtAttrInfo_t  aExtAttrInfo[1];    // variable length array
} zclDiscoverAttrsExtRsp_t;

/*********************************************************************
 * Plugins
 */

// Incoming ZCL message, this buffer will be allocated, cmd will point to the
// the command record.
typedef struct
{
  afIncomingMSGPacket_t *msg;        // incoming message
  zclFrameHdr_t         hdr;         // ZCL header parsed
  uint8                 *pData;      // pointer to data after header
  uint16                pDataLen;    // length of remaining data
  void                  *attrCmd;    // pointer to the parsed attribute or command
} zclIncoming_t;

// Outgoing ZCL Cluster Specific Commands
typedef struct
{
  zclFrameHdr_t hdr;
  uint16        realClusterID;
  uint16        attrID;
  void          *cmdStruct;
  uint8         cmdLen;
  uint8         *cmdData;
} zclOutgoingCmd_t;

// Incoming ZCL message passed to the Application. This buffer will be
// allocated and attrCmd will point to the command record.
//
// NOTE - the Application must deallocate the message plus attrCmd buffer.
//
typedef struct
{
  osal_event_hdr_t hdr;         // OSAL header
  zclFrameHdr_t    zclHdr;      // ZCL header parsed
  uint16           clusterId;   // Cluster ID
  afAddrType_t     srcAddr;     // Sender's address
  uint8            endPoint;    // destination endpoint
  void             *attrCmd;    // pointer to the parsed attribute or command; must be freed by Application
} zclIncomingMsg_t;

// Function pointer type to handle incoming messages.
//   msg - incoming message
//   logicalClusterID - logical cluster ID
typedef ZStatus_t (*zclInHdlr_t)( zclIncoming_t *pInHdlrMsg );

// Function pointer type to handle incoming write commands.
//   msg - incoming message
//   logicalClusterID - logical cluster ID
//   writeRec - received data to be written
typedef ZStatus_t (*zclInWrtHdlr_t)( zclIncoming_t *msg, uint16 logicalClusterID, ZclWriteRec *writeRec );

// Command record
typedef struct
{
  uint16   clusterID;
  uint8    cmdID;
  uint8    flag;  // one of CMD_DIR_CLIENT_GENERATED, CMD_DIR_CLIENT_RECEIVED, CMD_DIR_SERVER_GENERATED, CMD_DIR_SERVER_RECEIVED
} zclCommandRec_t;



// Function pointer type to validate attribute data.
//
//   pAttr - where data to be written
//   pAttrInfo - pointer to attribute info
//
//   return  TRUE if data valid. FALSE, otherwise.
typedef uint8 (*zclValidateAttrData_t)(struct zclAttrRec_t *pAttr, ZclWriteRec *pAttrInfo );



typedef struct
{
  uint16  clusterID;      // Real cluster ID
  uint8   option;
} zclOptionRec_t;



/*********************************************************************
 * GLOBAL VARIABLES
 */
extern uint8 zcl_TaskID;
extern uint8 zcl_SeqNum;
extern uint8 zcl_TransID;

/*********************************************************************
 * FUNCTION MACROS
 */
#ifdef ZCL_WRITE
/*
 *  Send a Write Command - ZCL_CMD_WRITE
 *  Use like:
 *      ZStatus_t zcl_SendWrite( uint8 srcEP, afAddrType_t *dstAddr, uint16 realClusterID, ZclWriteCmd *writeCmd, uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );
 */
#define zcl_SendWrite(a,b,c,d,e,f,g) (zcl_SendWriteRequest( (a), (b), (c), (d), ZCL_CMD_WRITE, (e), (f), (g) ))

/*
 *  Send a Write Undivided Command - ZCL_CMD_WRITE_UNDIVIDED
 *  Use like:
 *      ZStatus_t zcl_SendWriteUndivided( uint8 srcEP, afAddrType_t *dstAddr, uint16 realClusterID, ZclWriteCmd *writeCmd, uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );
 */
#define zcl_SendWriteUndivided(a,b,c,d,e,f,g) (zcl_SendWriteRequest( (a), (b), (c), (d), ZCL_CMD_WRITE_UNDIVIDED, (e), (f), (g) ))

/*
 *  Send a Write No Response Command - ZCL_CMD_WRITE_NO_RSP
 *  Use like:
 *      ZStatus_t zcl_SendWriteNoRsp( uint8 srcEP, afAddrType_t *dstAddr, uint16 realClusterID, ZclWriteCmd *writeCmd, uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );
 */
#define zcl_SendWriteNoRsp(a,b,c,d,e,f,g) (zcl_SendWriteRequest( (a), (b), (c), (d), ZCL_CMD_WRITE_NO_RSP, (e), (f), (g) ))
#endif // ZCL_WRITE

#define zcl_mem_alloc      osal_mem_alloc
#define zcl_memset         osal_memset
#define zcl_memcpy         osal_memcpy
#define zcl_mem_free       osal_mem_free
#define zcl_buffer_uint32  osal_buffer_uint32
#define zcl_nv_item_init   osal_nv_item_init
#define zcl_nv_write       osal_nv_write
#define zcl_nv_read        osal_nv_read
#define zcl_build_uint32   osal_build_uint32
#define zcl_cpyExtAddr     osal_cpyExtAddr

/*********************************************************************
 * FUNCTIONS
 */

 /*
  * callback function to handle messages externally
  */
extern uint8 zcl_HandleExternal( zclIncoming_t *pInMsg );
extern void zcl_Init( byte task_id );
extern UINT16 zcl_event_loop( byte task_id, UINT16 events );
extern uint8 zcl_registerForMsg( uint8 taskId );

/*
 *  Function for Plugins' to register for incoming messages
 */
extern ZStatus_t zcl_registerPlugin( uint16 startLogCluster, uint16 endLogCluster, zclInHdlr_t pfnIncomingHdlr );

/*
 *  Register Application's Command table
 */
extern ZStatus_t zcl_registerCmdList( uint8 endpoint, CONST uint8 cmdListSize, CONST zclCommandRec_t newCmdList[] );

/*
 *  Register Application's Cluster Option table
 */
extern ZStatus_t zcl_registerClusterOptionList( uint8 endpoint, uint8 numOption, zclOptionRec_t optionList[] );

/*
 *  Register Application's attribute data validation callback routine
 */
extern ZStatus_t zcl_registerValidateAttrData( zclValidateAttrData_t pfnValidateAttrData );

/*
 *  Process incoming ZCL messages
 */
extern zclProcMsgStatus_t zcl_ProcessMessageMSG( afIncomingMSGPacket_t *pkt );

/*
 *  Function for Sending a Command
 */
extern ZStatus_t zcl_SendCommand( uint8 srcEP, afAddrType_t *dstAddr, uint16 clusterID, uint8 cmd, uint8 specific, uint8 direction, uint8 disableDefaultRsp, uint16 manuCode, uint8 seqNum, uint16 cmdFormatLen, uint8 *cmdFormat );
extern ZStatus_t zclSendCommand( uint8 srcEP, afAddrType_t *dstAddr, uint16 clusterID, uint8 cmd, uint8 specific, uint8 direction, uint8 disableDefaultRsp, uint16 manuCode, uint8 seqNum, BufferData & bufferData );


/*
 *  Function for Reading an Attribute
 */
extern ZStatus_t zcl_SendRead( uint8 srcEP, afAddrType_t *dstAddr,  uint16 realClusterID, zclReadCmd_t *readCmd, uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 *  Function for sending a Read response command
 */
extern ZStatus_t zcl_SendReadRsp( uint8 srcEP, afAddrType_t *dstAddr,
                                  uint16 realClusterID, zclReadRspCmd_t *readRspCmd,
                                  uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 *  Function for reading a local attribute
 */
extern ZStatus_t zcl_ReadAttrData( uint8 endpoint, uint16 clusterId, uint16 attrId,
                                   uint8 *pAttrData, uint16 *pDataLen );


#ifdef ZCL_WRITE
/*
 *  Function for Writing an Attribute
 */
extern ZStatus_t zcl_SendWriteRequest( uint8 srcEP, afAddrType_t *dstAddr,
                                       uint16 realClusterID, ZclWriteCmd *writeCmd,
                                       uint8 cmd, uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 *  Function for sending a Write response command
 */
extern ZStatus_t zcl_SendWriteRsp( uint8 srcEP, afAddrType_t *dstAddr,
                                   uint16 realClusterID, ZclWriteRspCmd *writeRspCmd,
                                   uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );
#endif // ZCL_WRITE

#ifdef ZCL_REPORT
/*
 *  Function for Configuring the Reporting mechanism for one or more attributes
 */
extern ZStatus_t zcl_SendConfigReportCmd( uint8 srcEP, afAddrType_t *dstAddr,
                          uint16 realClusterID, zclCfgReportCmd_t *cfgReportCmd,
                          uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 *  Function for sending a Configure Reporting Response Command
 */
extern ZStatus_t zcl_SendConfigReportRspCmd( uint8 srcEP, afAddrType_t *dstAddr,
                    uint16 realClusterID, zclCfgReportRspCmd_t *cfgReportRspCmd,
                    uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 *  Function for Reading the configuration details of the Reporting mechanism
 */
extern ZStatus_t zcl_SendReadReportCfgCmd( uint8 srcEP, afAddrType_t *dstAddr,
                              uint16 realClusterID, zclReadReportCfgCmd_t *readReportCfgCmd,
                              uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 *  Function for sending a Read Reporting Configuration Response command
 */
extern ZStatus_t zcl_SendReadReportCfgRspCmd( uint8 srcEP, afAddrType_t *dstAddr,
                        uint16 realClusterID, zclReadReportCfgRspCmd_t *readReportCfgRspCmd,
                        uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 *  Function for Reporting the value of one or more attributes
 */
extern ZStatus_t zcl_SendReportCmd( uint8 srcEP, afAddrType_t *dstAddr,
                              uint16 realClusterID, zclReportCmd_t *reportCmd,
                              uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );
#endif // ZCL_REPORT

/*
 *  Function for sending the Default Response command
 */
extern ZStatus_t zcl_SendDefaultRspCmd( uint8 srcEP, afAddrType_t *dstAddr, uint16 realClusterID,
                                        zclDefaultRspCmd_t *defaultRspCmd, uint8 direction,
                                        uint8 disableDefaultRsp, uint16 manuCode, uint8 seqNum );

#ifdef ZCL_DISCOVER
/*
 *  Function to Discover the ID and Types of commands on a remote device
 */
extern ZStatus_t zcl_SendDiscoverCmdsCmd( uint8 srcEP, afAddrType_t *dstAddr,
                            uint16 clusterID, uint8 cmdType, zclDiscoverCmdsCmd_t *pDiscoverCmd,
                            uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 *  Function for sending the Discover Commands Response command
 */
extern ZStatus_t zcl_SendDiscoverCmdsRspCmd( uint8 srcEP, afAddrType_t *dstAddr,
                          uint16 clusterID, zclDiscoverCmdsCmdRsp_t *pDiscoverRspCmd,
                          uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 *  Function to Discover the ID and Types of the Attributes on a remote device
 */
extern ZStatus_t zcl_SendDiscoverAttrsCmd( uint8 srcEP, afAddrType_t *dstAddr,
                            uint16 realClusterID, zclDiscoverAttrsCmd_t *pDiscoverCmd,
                            uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 *  Function for sending the Discover Attributes Response command
 */
extern ZStatus_t zcl_SendDiscoverAttrsRspCmd( uint8 srcEP, afAddrType_t *dstAddr,
                      uint16 realClusterID, zclDiscoverAttrsRspCmd_t *pDiscoverRspCmd,
                      uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 * Function for sending the Discover Attributes Extended command
 */
extern ZStatus_t zcl_SendDiscoverAttrsExt( uint8 srcEP, afAddrType_t *dstAddr,
                                     uint16 realClusterID, zclDiscoverAttrsCmd_t *pDiscoverAttrsExt,
                                     uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );

/*
 * Function for sending the Discover Attributes Extended Response command
 */
extern ZStatus_t zcl_SendDiscoverAttrsExtRsp( uint8 srcEP, afAddrType_t *dstAddr,
                                         uint16 realClusterID, zclDiscoverAttrsExtRsp_t *pDiscoverAttrsExtRsp,
                                         uint8 direction, uint8 disableDefaultRsp, uint8 seqNum );
#endif // ZCL_DISCOVER

#ifdef ZCL_READ
/*
 * Function to parse the "Profile" Read Commands
 */
extern void *zclParseInReadCmd( zclParseCmd_t *pCmd );
#endif // ZCL_READ

#ifdef ZCL_WRITE
/*
 * Function to parse the "Profile" Write, Write Undivided and Write No Response
 * Commands
 */
extern void *zclParseInWriteCmd( zclParseCmd_t *pCmd );
#endif // ZCL_WRITE

#ifdef ZCL_REPORT
/*
 * Function to parse the "Profile" Configure Reporting Command
 */
extern void *zclParseInConfigReportCmd( zclParseCmd_t *pCmd );
/*
 * Function to parse the "Profile" Read Reporting Configuration Command
 */
extern void *zclParseInReadReportCfgCmd( zclParseCmd_t *pCmd );
/*
 * Function to parse the "Profile" Report attribute Command
 */
extern void *zclParseInReportCmd( zclParseCmd_t *pCmd );

/*
 * Function to check to see if Data Type is Analog
 */
extern uint8 zclAnalogDataType( uint8 dataType );
#endif // ZCL_REPORT

#ifdef ZCL_DISCOVER
/*
 * Function to parse the "Profile" Discover Commands Command
 */
extern void *zclParseInDiscCmdsCmd( zclParseCmd_t *pCmd );

/*
 * Function to parse the "Profile" Discover Attributes and Attributes Extended Commands
 */
extern void *zclParseInDiscAttrsCmd( zclParseCmd_t *pCmd );

/*
 * Function to find the command record that matchs the parameters
 */
extern uint8 zclFindCmdRec( uint8 endpoint, uint16 clusterID, uint8 cmdID, zclCommandRec_t *pCmd );
#endif // ZCL_DISCOVER

/*
 * Function to parse header of the ZCL format
 */
extern uint8 *zclParseHdr( zclFrameHdr_t *hdr, uint8 *pData );



/*
 * Function to read the attribute's current value
 */
extern ZStatus_t zclReadAttrData( uint8 *pAttrData,struct zclAttrRec_t *pAttr, uint16 *pDataLen );



/*
 * Function to serialize attribute data.
 */
extern uint8 *zclSerializeData( uint8 dataType, void *attrData, uint8 *buf );


/*
 * Call to get original unprocessed AF message (not parsed by ZCL).
 *
 *   NOTE:  This function can only be called during a ZCL callback function
 *          and the calling function must NOT change any data in the message.
 *
 *  returns a pointer to original AF message, NULL if not processing
 *          AF message.
 */
extern afIncomingMSGPacket_t *zcl_getRawAFMsg( void );

/*
 * Call to the get the transaction sequence number from the incoming message.
 *
 *   NOTE:  This function can only be called during a ZCL callback function
 *          and the calling function must NOT change any data in the message.
 *
 * returns the transaction sequence number.
 */
extern uint8 zcl_getParsedTransSeqNum( void );



/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* ZCL_H */
