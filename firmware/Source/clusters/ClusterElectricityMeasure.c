
/**************************************************************************************************

 DESCRIPTION:
  --

 CREATED: 05/11/2015, by Paolo Achdjian

 FILE: ClusterElectricityMeasure.c

***************************************************************************************************/


#include "zcl.h"
#include "ClusterElectricityMeasure.h"


uint32 measurementType=0x0107;
uint16 frequency=220;
int32 totalActivePower=0;
int32 totalReactivePower=0;
uint32 totalApparentPower=0;
uint16 frequencyMult=1;
uint16 frequencyDiv=1;
uint32 powerMult=1;
uint32 powerDivisor=1;

uint16 acVoltMult=1;
uint16 acVoltDiv=1;
uint16 acCurrentMult=1;
uint16 acCurrentDiv=1;
uint16 acPowerMult=1;
uint16 acPowerDiv=1;

uint16 tmp;

uint16 lineCurrent;
int16 activeCurrent;
int16 reactiveCurrent;
uint16 RMSVolt;
uint16 RMSVoltMin;
uint16 RMSVoltMax;
uint16 RMSCurrent;
uint16 RMSCurrentMinx;
uint16 RMSCurrentMax;
int16 ActivePower;
int16 ActivePowerMinx;
int16 ActivePowerMax;
int16 ReactivePower;
uint16 ApparentPower;
int8 PowerFactor;
uint16 averageRmsVolrPeriod;


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
	case ATTRID_ELECTRICITY_MEASURE_TOTAL_ACTIVE_POWER:
		attribute->dataType = ZCL_DATATYPE_INT32;
		attribute->dataPtr = (void *)&totalActivePower;
		break;	
	case ATTRID_ELECTRICITY_MEASURE_TOTAL_REACTIVE_POWER:
		attribute->dataType = ZCL_DATATYPE_INT32;
		attribute->dataPtr = (void *)&totalReactivePower;
		break;		
	case ATTRID_ELECTRICITY_MEASURE_TOTAL_APPARENT_POWER:
		attribute->dataType = ZCL_DATATYPE_INT32;
		attribute->dataPtr = (void *)&totalApparentPower;
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
	case ATTRID_ELECTRICITY_MEASURE_LINE_CURRENT:
		tmp = getCS5463RegisterValue(IstantaneoCurrent) >> 8;
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&tmp;
		break;
	case ATTRID_ELECTRICITY_MEASURE_RMS_VOLT:
		tmp = getCS5463RegisterValue(RMSVolt) >> 8;
		attribute->dataType = ZCL_DATATYPE_UINT16;
		attribute->dataPtr = (void *)&tmp;
		break;
	default:
		attribute->status = ZCL_STATUS_UNSUPPORTED_ATTRIBUTE;
	}
}