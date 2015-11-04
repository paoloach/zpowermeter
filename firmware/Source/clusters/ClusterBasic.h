/**************************************************************************************************
  Filename:       ClusterBasic.h

  Autorh:  Paolo Achdjia
  Created: 28/10/2014

**************************************************************************************************/

#ifndef __CLUSTER_BASIC__H__
#define __CLUSTER_BASIC__H__

#include "zcl_general.h"
#include "zcl.h"
#include "zclReadAttributeFn.h"
#include "zclWriteAttributeFn.h"

extern const uint8 HWRevision;
extern const uint8 ZCLVersion;
extern const uint8 manufacturerName[];
extern const uint8 modelId[];
extern const uint8 dateCode[];
extern const uint8 powerSource;
extern uint8 locationDescription[];
extern uint8 physicalEnvironment;
extern uint8 deviceEnable;

void basicResetCB( void );
void basicClusterReadAttribute(zclAttrRec_t *);
void basicClusterWriteAttribute(ZclWriteAttribute_t *);
ZStatus_t processBasicClusterCommands( zclIncoming_t *pInMsg );


#endif