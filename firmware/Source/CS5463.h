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
	IstantaneoCurrent=7,
	RMSVolt = 12
};

extern void CS5463_Init(void);

extern void CS5463_startConversion(void);

extern int32 getCS5463RegisterValue(enum CS5463Register regIndex);


#endif