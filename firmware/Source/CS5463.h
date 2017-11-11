/**************************************************************************************************

 DESCRIPTION:
  --

 CREATED: 14/10/2015, by Paolo Achdjian

 FILE: CS5463.h

***************************************************************************************************/
#ifndef __CS5463__H__
#define __CS5463__H__

#include "hal_types.h"

enum CS5463Register {
	Config=0,
	CurrentDCOffset=1,
	CurrentGain=2,
	VoltageDcOffset=3,
	VoltageGain=4,
	CycleCount=5,
	PulseRateE=6,
	IstantaneusCurrent=7,
	IstantaneusVoltage=8,
	IstantaneusPower=9,
	ActivePower=10,
	RMSCurrent = 11,
	RMSVolt = 12,
	Epsilon=13,
	PowerOffsetRegister=14,
	status = 15,
	CurrentAcOffsset=16,
	VoltageAcOffset=17,
	Mode=18,
	Temperature=19,
	AverageReactivePower=20,
	IstantaneusReactivePower=21,
	PeakCurrent=22,
	PeakVoltage=23,
	ReactivePowerReg=24,
	PowerFactor=25,
	MaskRegister=26,
	ApparentPower=27,
	ControlRegister=28,
	ArmonicActivePower=29,
	FundamentalActivePower=30,
	FundamentalReactivePower=31,
	PageRegister=31

	
};

extern void CS5463_Init(void);

extern void CS5463_startConversion(void);
extern void CS5463_reset(void);

extern int32 getCS5463RegisterValue(enum CS5463Register regIndex);
extern void setCS5463RegisterValue(enum CS5463Register regIndex,unsigned char byte1,unsigned char  byte2,unsigned char  byte3);


#endif