#include "ClusterElectricityMeasure.h"

uint32 measurementType=0x0107;
uint16 frequency=220;
int32 totalActivePower;
int32 totalReactivePower;
uint32 totalApparentPower;
uint16 frequencyMult=1;
uint16 frequencyDiv=1;
uint32 powerMult=1;
uint32 powerDivisor=1;

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
uint16 acVoltMult;
uint16 acVoltDiv;
uint16 acCurrentMult;
uint16 acCurrentDiv;
uint16 acPowerMult;
uint16 acPowerDiv;

void electricityMeasureClusterReadAttribute(zclAttrRec_t * attribute){
	
}