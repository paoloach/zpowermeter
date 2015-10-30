#ifndef __ZCL_READ_CMD__H__
#define __ZCL_READ_CMD__H__

#include "hal_types.h"
#include "zclParseCmd.h"
#include "OSAL_Memory.h"
#include "BufferData.h"

class zclReadCmd_t{
public:
	zclReadCmd_t(zclParseCmd_t * pCmd);
	inline ~zclReadCmd_t(){osal_mem_free(attrID);}
	BufferData getBufferFromAttribute();
	uint8  numAttr;            // number of attributes in the list
	uint16 * attrID;
} ;
#endif