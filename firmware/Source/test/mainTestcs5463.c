/**************************************************************************************************

 DESCRIPTION:
  --

 CREATED: 06/11/2015, by Paolo Achdjian

 FILE: mainTestcs5463.c

***************************************************************************************************/



#include "hal_adc.h"
#include "hal_flash.h"
#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_drivers.h"
#include "OnBoard.h"
#include "OSAL.h"
#include "OSAL_Nv.h"

#include "clusters/ClusterIdentify.h"
#include "clusters/ClusterOnOff.h"
#include "CS5463.h"


__sfr __no_init volatile struct  {
	unsigned char DIR0_0: 1;
	unsigned char DIR0_1: 1;
	unsigned char DIR0_2: 1;
	unsigned char DIR0_3: 1;
	unsigned char DIR0_4: 1;
	unsigned char DIR0_5: 1;
	unsigned char DIR0_6: 1;
	unsigned char DIR0_7: 1;
} @ 0xFD;

__sfr __no_init volatile struct  {
	unsigned char DIR1_0: 1;
	unsigned char DIR1_1: 1;
	unsigned char DIR1_2: 1;
	unsigned char DIR1_3: 1;
	unsigned char DIR1_4: 1;
	unsigned char DIR1_5: 1;
	unsigned char DIR1_6: 1;
	unsigned char DIR1_7: 1;
} @ 0xFE;


__sfr __no_init volatile struct  {
	unsigned char P0SEL_0: 1;
	unsigned char P0SEL_1: 1;
	unsigned char P0SEL_2: 1;
	unsigned char P0SEL_3: 1;
	unsigned char P0SEL_4: 1;
	unsigned char P0SEL_5: 1;
	unsigned char P0SEL_6: 1;
	unsigned char P0SEL_7: 1;
} @ 0xF3;

__sfr __no_init volatile struct  {
	unsigned char P1SEL_0: 1;
	unsigned char P1SEL_1: 1;
	unsigned char P1SEL_2: 1;
	unsigned char P1SEL_3: 1;
	unsigned char P1SEL_4: 1;
	unsigned char P1SEL_5: 1;
	unsigned char P1SEL_6: 1;
	unsigned char P1SEL_7: 1;
} @ 0xF4;

static void identifyLED(void);
static void connectionLED(void);
static void onLED(void);

static void onOff(void);

/*********************************************************************
 * @fn      zmain_vdd_check
 * @brief   Check if the Vdd is OK to run the processor.
 * @return  Return if Vdd is ok; otherwise, flash LED, then reset
 *********************************************************************/
static void zmain_vdd_check( void )
{
  uint8 cnt = 16;
  
  do {
    while (!HalAdcCheckVdd(VDD_MIN_RUN));
  } while (--cnt);
}

volatile uint32 value5463;
volatile uint32 reg00;
volatile uint32 reg01;
volatile uint32 reg02;
volatile uint32 reg03;
volatile uint32 reg04;
volatile uint32 reg05;
volatile uint32 reg11;
volatile uint32 reg12;
volatile uint32 reg15;
volatile uint32 reg18;

int main() {
	 // Turn off interrupts
  //osal_int_disable( INTS_ALL );

  // Initialization for board related stuff such as LEDs
  //HAL_BOARD_INIT();

  // Make sure supply voltage is high enough to run
  zmain_vdd_check();

  // Initialize board I/O
  //InitBoard( OB_COLD );

  // Initialze HAL drivers
  //HalDriverInit();

  // Initialize NV System
 // osal_nv_init( NULL );
 // Initialize the operating system
  //osal_init_system();

  // Allow interrupts
  //osal_int_enable( INTS_ALL );

  // Final board initialization
 // InitBoard( OB_READY );
//	identifyLED();
//	connectionLED();
//	onLED();
  CS5463_Init();
    CS5463_reset();
  
	
	setCS5463RegisterValue(CycleCount,0x00, 0x0F, 0xA0);
  
  setCS5463RegisterValue(Config,0x01, 0x00, 0x01);
  setCS5463RegisterValue(Mode,0x00, 0x00, 0x60);
  CS5463_startConversion();
  
  while(1){
	  reg00 = getCS5463RegisterValue(Config);
	
	  reg02 = getCS5463RegisterValue(CurrentGain);
	  reg03 = getCS5463RegisterValue(VoltageDcOffset);
	  reg04 = getCS5463RegisterValue(VoltageGain);
	  reg05 = getCS5463RegisterValue(CycleCount);
	  reg11 = getCS5463RegisterValue(RMSCurrent);
	  reg12 = getCS5463RegisterValue(RMSVolt);
	  reg18 = getCS5463RegisterValue(Mode);
	  
	  // MULT = 0.250 * 2000;
	  // DIV = 0x1000000
	 
	  
  		reg15 = getCS5463RegisterValue(status);
		if (P1_2 == 1){
			setLightStatus(LIGHT_ON);
		} else {
			setLightStatus(LIGHT_OFF);
		}
  }
  
}


static void identifyLED(void) {
	identifyInit(1);
	for(uint8 i=0; i <25; i++){
		P1_1= 1;
		for(uint16 y=0; y < 40000; y++);
		P1_1=0;
		for(uint16 y=0; y < 40000; y++);
	}
}

static void connectionLED(void) {
	DIR1_0 = 1;
 	P1SEL_0 = 0;
	for(uint8 i=0; i < 10; i++){
		P1_0 = 1;
		for(uint16 y=0; y < 40000; y++);
		P1_0=0;
		for(uint16 y=0; y < 40000; y++);
	}
}

static void onLED(void) {
	DIR0_7 = 1;
 	P0SEL_7 = 0;
	for(uint8 i=0; i < 10; i++){
		P0_7 = 1;
		for(uint16 y=0; y < 40000; y++);
		P0_7=0;
		for(uint16 y=0; y < 40000; y++);
	}
}

static void onOff(void) {
	onOffInit();
	while(1){
		if (P1_2 == 1){
			setLightStatus(LIGHT_ON);
		} else {
			setLightStatus(LIGHT_OFF);
		}
	}
}