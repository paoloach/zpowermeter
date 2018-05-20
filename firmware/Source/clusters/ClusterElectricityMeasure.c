
/**************************************************************************************************

 DESCRIPTION:
  --

 CREATED: 05/11/2015, by Paolo Achdjian

 FILE: ClusterElectricityMeasure.c

***************************************************************************************************/


#include "zcl.h"
#include "ClusterElectricityMeasure.h"
#include "CS5463.h"


static uint32 measurementType=0x0107;
static uint16 frequency=220;
static uint16 frequencyMult=1;
static uint16 frequencyDiv=1;
static uint32 powerMult=1;
static uint32 powerDivisor=1;

/*
  From the schematic, the voltage is divided by 1601 first to send to cs5463
  So 220V ->137mv, that is 0.548 of the full scale voltage (250 mv)

  The value read by CS5463 is multiply for 0x1000, in order to obtaion a value from -0x1000 to 0x1000, where 0x1000 is 250mv, so to obtain the value read from cs5463
  
  val /(4*0x1000)

  Because the value read by cs5462 was divided by 2000, then it's need to multiplay for the same value.
  
*/
static uint16 acVoltMult=1601;
static uint16 acVoltDiv=0x4000;

static uint16 T_shunt = 10;
static uint16 acCurrentMult=1;
static uint16 acCurrentDiv=1;
static uint16 acPowerMult=1;
static uint16 acPowerDiv=1;

static uint16 tmp;

static uint16 averageRmsVolrPeriod;

static struct ElectricityCalibration calibration = {0x000000, 0x000000, 0x400000, 0x400000, 0x000000, 0x000000};

void electricityMeasureClusterInit(void) {;
	CS5463_Init();
	
	volatile uint32 tmp;
		
	setCS5463RegisterValue(Config, 0x0,0x00, 0x01);
	setCS5463RegisterValue(Mode, 0x00,0x00, 0x61);
	setCS5463RegisterValue(MaskRegister, 0x00,0x00, 0x00);
	setCS5463RegisterValue(ControlRegister, 0x00,0x00, 0x04);
	setCS5463RegisterValue(status, 0x00,0x00, 0x00);
	
	osal_nv_item_init(NV_ELECTRICITY_MEASURE_CALIBRATION, sizeof(struct ElectricityCalibration), &calibration);
	osal_nv_read(NV_ELECTRICITY_MEASURE_CALIBRATION, 0,  sizeof(struct ElectricityCalibration), &calibration);
/*	
	setCS5463RegisterValue32(CurrentDcOffset, calibration.IDC_Offset);
	setCS5463RegisterValue32(VoltageDcOffset, calibration.VDC_Offset);
	setCS5463RegisterValue32(VoltageGain, calibration.V_Gain);
	setCS5463RegisterValue32(CurrentGain, calibration.I_Gain);
	setCS5463RegisterValue32(CurrentAcOffset, calibration.IAC_Offset);
	setCS5463RegisterValue32(VoltageAcOffset, calibration.VAC_Offset);
*/
	
//	CS5463_startConversion();
}


static void calibrateVDCOffset(void);
static void calibrateIDCOffset(void);
static void calibrateVACOffset(void);
static void calibrateIACOffset(void);

static void calibrateVGain(uint8 expectedVolt);
static void calibrateIGain(uint16 expectedMilAmpere);

ZStatus_t processElectricityMeasureClusterServerCommands( zclIncoming_t *pInMsg ){
	switch(pInMsg->hdr.commandID){
	case COMMAND_CALIBRATE_V_DC_OFFSET:
		setCS5463RegisterValue32(status,0);
		return ZSuccess;
	case COMMAND_CALIBRATE_I_DC_OFFSET:
		calibrateIDCOffset();
		return ZSuccess;
	case COMMAND_CALIBRATE_V_AC_OFFSET:
		calibrateVACOffset();
		return ZSuccess;
	case COMMAND_CALIBRATE_I_AC_OFFSET:
		calibrateIACOffset();
		return ZSuccess;
	case COMMAND_CALIBRATE_V_GAIN:{
			uint8 expectedVolt = pInMsg->pData[0];
			calibrateVGain(expectedVolt);
		}
		return ZSuccess;		
	case COMMAND_CALIBRATE_I_GAIN:{
			uint16 expectedMilAmpere= BUILD_UINT16( pInMsg->pData[0], pInMsg->pData[1] );
			calibrateIGain(expectedMilAmpere);
		}
		return ZSuccess;		
	case COMMAND_START_MEASURE:
		CS5463_startConversion();
		return ZSuccess;	
	case COMMAND_START_SINGLE_MEASURE:
		setCS5463RegisterValue(status, 0x00,0x00, 0x00);
		return ZSuccess;	
	case COMMAND_RESET:
		CS5463_reset();
		return ZSuccess;			
	default:
    	return ZFailure;   // Error ignore the command
	}
}

static void calibrateVDCOffset(void) {
	calibration.VDC_Offset = getCS5463RegisterValue(RMSVolt);
	CS5463_startCalibration(V_DC_OFFSET);
	calibration.VDC_Offset = getCS5463RegisterValue(VoltageDcOffset);
	osal_nv_write(NV_ELECTRICITY_MEASURE_CALIBRATION, 0, sizeof(struct ElectricityCalibration), &calibration);
}
	
static void calibrateIDCOffset(void) {
	CS5463_startCalibration(I_DC_OFFSET);
	calibration.IDC_Offset = getCS5463RegisterValue(CurrentDcOffset);
	osal_nv_write(NV_ELECTRICITY_MEASURE_CALIBRATION, 0, sizeof(struct ElectricityCalibration), &calibration);
}


static void calibrateVACOffset(void) {
	CS5463_startCalibration(V_AC_OFFSET);
	
//	uint32 val = getCS5463RegisterValue(RMSVolt);
//	calibration.VAC_Offset = val;
//	osal_nv_write(NV_ELECTRICITY_MEASURE_CALIBRATION, 0, sizeof(struct ElectricityCalibration), &calibration);
//	setCS5463RegisterValue32(VoltageAcOffset,val);
}
	
	
static void calibrateIACOffset(void) {
	CS5463_startCalibration(I_AC_OFFSET);
}

static void calibrateVGain(uint8 expectedVolt) {
	
	uint32 expectedInVolt = ((uint32)expectedVolt << 22)/acVoltMult;
	
	uint32 volt = getCS5463RegisterValue(RMSVolt);
	calibration.V_Gain = expectedInVolt/volt;
	setCS5463RegisterValue32(VoltageGain, calibration.V_Gain);

	osal_nv_write(NV_ELECTRICITY_MEASURE_CALIBRATION, 0, sizeof(struct ElectricityCalibration), &calibration);
}


static void calibrateIGain(uint16 expectedMilAmpere) {
	
	uint32 expectedInCurrent = ((uint32)expectedMilAmpere << 22 )/(1000*T_shunt);
	uint32 current = getCS5463RegisterValue(RMSCurrent);
	calibration.I_Gain = expectedInCurrent/current;		
	setCS5463RegisterValue32(VoltageGain, calibration.V_Gain);

	osal_nv_write(NV_ELECTRICITY_MEASURE_CALIBRATION, 0, sizeof(struct ElectricityCalibration), &calibration);
}	
		



void electricityMeasureClusterReadAttribute(zclAttrRec_t * attribute){
	if (attribute == NULL){
		return;
	}
	attribute->accessControl = ACCESS_CONTROL_READ;
	attribute->status =  ZCL_STATUS_SUCCESS;
	switch(attribute->attrId){
	case ATTRID_ELECTRICITY_MEASURE_MEASUREMENT_TYPE:
		attribute->dataType = ZCL_DATATYPE_BITMAP32;
		attribute->dataPtr = (void *)&measurementType;
		break;
	case ATTRID_ELECTRICITY_MEASURE_AC_FREQ:
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&frequency;
		break;		
	case ATTRID_ELECTRICITY_MEASURE_AC_FREQ_MULT:
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&frequencyMult;
		break;
	case ATTRID_ELECTRICITY_MEASURE_AC_FREQ_DIV:
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&frequencyDiv;
		break;
	case ATTRID_ELECTRICITY_MEASURE_POWER_MULT:
		attribute->dataType = ZCL_DATATYPE_UINT32;
		attribute->dataPtr = (void *)&powerMult;
		break;
	case ATTRID_ELECTRICITY_MEASURE_POWER_DIV:
		attribute->dataType = ZCL_DATATYPE_UINT32;
		attribute->dataPtr = (void *)&powerDivisor;
		break;
	case ATTRID_ELECTRICITY_MEASURE_AV_RMS_VOLT_PERIOD:
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&averageRmsVolrPeriod;
		break;
	case ATTRID_ELECTRICITY_MEASURE_AC_VOLT_MULT:
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&acVoltMult;
		break;
	case ATTRID_ELECTRICITY_MEASURE_AC_VOLT_DIV:
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&acVoltDiv;
		break;
	case ATTRID_ELECTRICITY_MEASURE_AC_CURRENT_MULT:
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&acCurrentMult;
		break;
	case ATTRID_ELECTRICITY_MEASURE_AC_CURRENT_DIV:
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&acCurrentDiv;
		break;
	case ATTRID_ELECTRICITY_MEASURE_AC_POWER_MULT:
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&acPowerMult;
		break;
	case ATTRID_ELECTRICITY_MEASURE_AC_POWER_DIV:
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&acPowerDiv;
		break;
		
	case ATTRID_ELECTRICITY_MEASURE_LINE_CURRENT:
		tmp = getCS5463RegisterValue(IstantaneusCurrent) >> 8;
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&tmp;
		break;
	case ATTRID_ELECTRICITY_MEASURE_RMS_VOLT:
		tmp = getCS5463RegisterValue(RMSVolt) >> 8;
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&tmp;
		break;
	case ATTRID_ELECTRICITY_MEASURE_RMS_CURRENT:
		tmp = getCS5463RegisterValue(RMSCurrent) >> 8;
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&tmp;
		break;
	case ATTRID_ELECTRICITY_MEASURE_RMS_CURRENT_MAX:
		tmp = getCS5463RegisterValue(PeakCurrent) >> 8;
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&tmp;
		break;
	case ATTRID_ELECTRICITY_MEASURE_ACTIVE_POWER:
		tmp = getCS5463RegisterValue(ActivePower) >> 8;
		attribute->dataType = ZCL_DATATYPE_INT16;
		attribute->dataPtr = (void *)&tmp;
		break;
	case ATTRID_ELECTRICITY_MEASURE_REACTIVE_POWER:
		tmp = getCS5463RegisterValue(IstantaneusReactivePower) >> 8;
		attribute->dataType = ZCL_DATATYPE_INT16;
		attribute->dataPtr = (void *)&tmp;
		break;
	case ATTRID_ELECTRICITY_MEASURE_APPARENT_POWER:
		tmp = getCS5463RegisterValue(ApparentPower) >> 8;
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&tmp;
		break;
	case ATTRID_ELECTRICITY_MEASURE_POWER_FACTOR:
		tmp = getCS5463RegisterValue(PowerFactor) >> 8;
		attribute->dataType = ZCL_DATATYPE_INT8;
		attribute->dataPtr = (void *)&tmp;
		break;
	default:
		attribute->status = ZCL_STATUS_UNSUPPORTED_ATTRIBUTE;
	}
}