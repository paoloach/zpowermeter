#ifndef __CLUSTER_ELECTRICITY_MEASURE__H__
#define __CLUSTER_ELECTRICITY_MEASURE__H__

#include "ClusterElectricityMeasure_constant.h"
#include <hal_types.h>
#include "zclReadAttributeFn.h"


#define NV_ELECTRICITY_MEASURE_CALIBRATION	0x401


#define COMMAND_CALIBRATE_V_DC_OFFSET             0x10 // 16
#define COMMAND_CALIBRATE_I_DC_OFFSET             0x11 // 17
#define COMMAND_CALIBRATE_V_AC_OFFSET             0x12 // 18
#define COMMAND_CALIBRATE_I_AC_OFFSET             0x13 // 19
#define COMMAND_CALIBRATE_V_GAIN	              0x14 // 20
#define COMMAND_CALIBRATE_I_GAIN    	          0x15 // 21
#define COMMAND_START_MEASURE	    	          0x16 // 22
#define COMMAND_START_SINGLE_MEASURE   	          0x17 // 23
#define COMMAND_RESET				   	          0x18 // 24



void electricityMeasureClusterInit(void);
void electricityMeasureClusterReadAttribute(zclAttrRec_t *);
ZStatus_t processElectricityMeasureClusterServerCommands( zclIncoming_t *pInMsg );

struct ElectricityCalibration {
	uint32 VDC_Offset;
	uint32 IDC_Offset;
	uint32 V_Gain;
	uint32 I_Gain;
	uint32 VAC_Offset;
	uint32 IAC_Offset;
	
};

#endif
