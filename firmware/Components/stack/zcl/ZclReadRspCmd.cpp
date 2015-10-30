
#include "ZclReadRspCmd.h"

ZclReadRspCmd::ZclReadRspCmd(zclReadCmd_t * readCmd, uint8 endpoint, uint16 clusterId) {
	struct zclAttrRec_t attrRec;
	attrList = new ZclReadRspStatus[readCmd->numAttr];
	ZclReadRspStatus * iter = attrList;
	uint16 * attrId = readCmd->attrID;
	for (int i=0; i < readCmd->numAttr; i++){
		iter->attrID = *attrId;
		
		if ( zclFindAttrRec( endpoint,clusterId, *attrId, &attrRec ) ){
			if ( zcl_AccessCtrlRead( attrRec.attr.accessControl ) ) {
				iter->status = zclAuthorizeRead(endPoint, &(pInMsg->msg->srcAddr), &attrRec );
				if ( iter->status == ZCL_STATUS_SUCCESS ) {
					iter->data = (unsigned char *)attrRec.attr.dataPtr;
					iter->dataType = attrRec.attr.dataType;
				}
			} else {
				iter->status = ZCL_STATUS_WRITE_ONLY;
			}
		} else {
			iter->status = ZCL_STATUS_UNSUPPORTED_ATTRIBUTE;
		}
		
		iter++;
		attrId++;
	}
}