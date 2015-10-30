#ifndef __ZCL_WRITE_CMD__H__
#define __ZCL_WRITE_CMD__H__

#include "hal_types.h"
#include "zclParseCmd.h"
#include "AttributeUtils.h"
#include "BufferData.h"

class ZclWriteRec{
public:
	uint16 attrID;             // attribute ID
	uint8  dataType;           // attribute data type
	uint8  *attrData;       
	
	uint16 getDataLen() {
		return 3 + zclGetAttrDataLength(dataType, attrData);
	}
};


class ZclWriteCmd{
public:
	ZclWriteCmd(zclParseCmd_t * );
	~ZclWriteCmd();
	BufferData getBufferFromAttribute();
private:
	uint16 getDataLen();
public:
	uint8         numAttr;     // number of attribute records in the list
	ZclWriteRec   * attrList;  // attribute records
	
	
};
#endif 