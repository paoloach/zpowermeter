#ifndef __ZCL_WRITE_RSP_CMD__H__
#define __ZCL_WRITE_RSP_CMD__H__

#include "hal_types.h"
#include "ZclWriteRspStatus.h"
#include "zclParseCmd.h"
#include "ZclWriteCmd.h"
#include "BufferData.h"

class ZclWriteRspCmd {
public:
	ZclWriteRspCmd(){
		numAttr=0;
		attrList=NULL;
	}
	ZclWriteRspCmd(ZclWriteRspCmd & a){
		numAttr = a.numAttr;
		attrList = a.attrList;
		a.numAttr=0;
		a.attrList=NULL;
	}
	ZclWriteRspCmd(zclParseCmd_t * pCmd);
	ZclWriteRspCmd(ZclWriteCmd * writeCmd);
	inline ~ZclWriteRspCmd(){delete attrList;}
	BufferData getBufferData();
	uint8               numAttr;    
	ZclWriteRspStatus  *attrList;
};

#endif