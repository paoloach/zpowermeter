/**************************************************************************************************

 DESCRIPTION:
  --

 CREATED: 14/10/2015, by Paolo Achdjian

 FILE: CS2530.c

***************************************************************************************************/
#include "ZComDef.h"
#include "OSAL.h"
#include "ioCC2530.h"
#include "CS5463.h"

// U0GCR
__sfr __no_init volatile struct  {
	unsigned char U0_CPOL: 1;
	unsigned char U0_CPHA: 1;
	unsigned char U0_ORDER: 1;
	unsigned char U0_BAUD_E: 5;
} @ 0xC5;

// U0CSR
__sfr __no_init volatile struct  {
	unsigned char U0_MODE: 1;
	unsigned char U0_RE: 1;
	unsigned char U0_SLAVE: 1;
	unsigned char U0_FE: 1;
	unsigned char U0_ERR: 1;
	unsigned char U0_RX_BYTE: 1;
	unsigned char U0_TX_BYTE: 1;
	unsigned char U0_ACTIVE: 1;
} @ 0x86;

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

union CS5463Reg {
	uint32	value;
	uint8	bytes[4];
};

void CS5463_Init(void ){
	U0_ACTIVE=0;
	U0BAUD=0;
	U0_BAUD_E=15;
	U0_CPOL=0;
	U0_CPHA=0;
	U0_ORDER=1;
	
	U0_MODE=0;
	U0_SLAVE=0;
	
	P0SEL_2=1;
	P0SEL_3=1;
	P0SEL_5=1;
	
	DIR0_7 = 1;
	P0SEL_7 = 0;
	P0_7=1;
	
	CS5463_startConversion();
}

void CS5463_startConversion(void) {
	P0_7=0;
	asm("NOP");
	asm("NOP");
	U0DBUF=0xE8;
	while(U0_TX_BYTE==0);
	asm("NOP");
	asm("NOP");
	P0_7=1;
}

int32 getCS5463RegisterValue(enum CS5463Register regIndex) {
	union CS5463Reg result;

	P0_7=0;
	asm("NOP");
	asm("NOP");
	uint8 index = (regIndex << 2);
	U0DBUF=index;
	asm("NOP");
	while(U0_TX_BYTE==0);
	result.bytes[3] = 0;
	U0DBUF=0xFF;
	asm("NOP");
	while(U0_TX_BYTE==0);
	
	result.bytes[2] = U0DBUF;
		
	U0DBUF=0xFF;
	asm("NOP");
	while(U0_TX_BYTE==0);
	result.bytes[1] = U0DBUF;
	U0DBUF=0xFF;
	asm("NOP");
	while(U0_TX_BYTE==0);
	result.bytes[0] = U0DBUF;
	asm("NOP");
	asm("NOP");
	P0_7=1;
	
	return result.value;
}

