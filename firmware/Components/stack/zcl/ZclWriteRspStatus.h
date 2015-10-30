#ifndef __ZCL_WRITE_RSP_STATUS__H__
#define __ZCL_WRITE_RSP_STATUS__H__
#include "hal_types.h"

class ZclWriteRspStatus {
public:
	uint8  status;             
	uint16 attrID;  
};

#endif