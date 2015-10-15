	/**************************************************************************************************
  Filename:       ClusterOnOff.c

  Autorh:  Paolo Achdjia
  Created: 27/10/2014

**************************************************************************************************/

#include "zcl_general.h"

#include "ClusterOnOff.h"
#include "onboard.h"

__sfr __no_init volatile struct  {
	unsigned char DIR0_7: 1;
	unsigned char DIR0_6: 1;
	unsigned char DIR0_5: 1;
	unsigned char DIR0_4: 1;
	unsigned char DIR0_3: 1;
	unsigned char DIR0_2: 1;
	unsigned char DIR0_1: 1;
	unsigned char DIR0_0: 1;
} @ 0xFD;

__sfr __no_init volatile struct  {
	unsigned char P0SEL_7: 1;
	unsigned char P0SEL_6: 1;
	unsigned char P0SEL_5: 1;
	unsigned char P0SEL_4: 1;
	unsigned char P0SEL_3: 1;
	unsigned char P0SEL_2: 1;
	unsigned char P0SEL_1: 1;
	unsigned char P0SEL_0: 1;
} @ 0xF3;

uint8  onOffValue = LIGHT_ON;

void onOffInit(void) {
	DIR0_0=1;
	P0SEL_0=0;
	P0_0=0;
}

void setIOStatus(void){
	if ( onOffValue  == LIGHT_ON )
	  P0_0=1;
  	else
	  P0_0=0;
}

void setLightStatus(uint8 status){
	onOffValue = status;
	setIOStatus();
}



ZStatus_t processOnOffClusterServerCommands(zclIncoming_t *pInMsg) {
	switch(pInMsg->hdr.commandID){
	case COMMAND_ON:
		onOffValue = LIGHT_ON;
		break;
	case COMMAND_OFF:
		onOffValue = LIGHT_OFF;
		break;
	case COMMAND_TOGGLE:
		if ( onOffValue == LIGHT_OFF )
      		onOffValue = LIGHT_ON;
    	else
      		onOffValue = LIGHT_OFF;
		break;
	default:
		return ZFailure;
	}
	setIOStatus();
	return ZSuccess;
}
