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

#include "CS5463.h"

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
  
  CS5463_Init();
  CS5463_startConversion();
  while(1){
  	uint32 value = getCS5463RegisterValue(IstantaneoCurrent);
  }
  
}

