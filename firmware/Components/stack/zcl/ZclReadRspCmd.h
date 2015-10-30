#ifndef __ZCL_READ_RSP_CMD__H__
#define __ZCL_READ_RSP_CMD__H__

#include "zclReadCmd_t.h"

struct ZclReadRspStatus{
public:
	uint16 attrID;            // attribute ID
	uint8  status;            // should be ZCL_STATUS_SUCCESS or error
	uint8  dataType;          // attribute data type
 	uint8  *data;             // this structure is allocated, so the data is HERE - the size depends on the attribute data type
};

// Read Attribute Response Command format
struct ZclReadRspCmd{
public:
	ZclReadRspCmd(zclReadCmd_t *);
	~ZclReadRspCmd(){
		delete attrList;
	}
	uint8              	numAttr;     // number of attributes in the list
	ZclReadRspStatus	* attrList;  // attribute status list
};

#endif