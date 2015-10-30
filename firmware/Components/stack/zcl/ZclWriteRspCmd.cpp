#include "ZclWriteRspCmd.h"
#include "OSAL_Memory.h"
#include "ZCL_StatusCode.h"

ZclWriteRspCmd::ZclWriteRspCmd(zclParseCmd_t * pCmd){
	uint16 dataLen = pCmd->dataLen;
	uint8 *pBuf = pCmd->pData;
	if (dataLen==1){
		attrList = new ZclWriteRspStatus[1];
		attrList->status = *pBuf;
	} else {
		numAttr = dataLen/3;
		attrList = new ZclWriteRspStatus[numAttr];
		for(uint8 i=0; i < numAttr; i++){
			attrList[i].status = *pBuf++;
        	attrList[i++].attrID = BUILD_UINT16( pBuf[0], pBuf[1] );
        	pBuf += 2;
		}
	}
}


ZclWriteRspCmd::ZclWriteRspCmd(ZclWriteCmd * writeCmd) {
	attrList = new ZclWriteRspStatus[writeCmd->numAttr];
	if (attrList != NULL){
		numAttr = writeCmd->numAttr;
	}
}

BufferData ZclWriteRspCmd::getBufferData() {
	if ( numAttr == 1 && attrList[0].status == ZCL_STATUS_SUCCESS ) {
    	BufferData buffer(1);
		if (buffer.isValid()){
			*buffer.data = ZCL_STATUS_SUCCESS;
		}
		return buffer;
    } else {
		uint16 dataLen = numAttr * ( 1 + 2 ); // status + attribute id
		BufferData buffer(dataLen);

		if ( buffer.isValid()){
			uint8 i;
			uint8 *pBuf = buffer.data;
			ZclWriteRspStatus * writeStatus = attrList;
    		for ( i = 0; i < numAttr; i++ ){
      			*pBuf++ = writeStatus->status;
	      		*pBuf++ = LO_UINT16( writeStatus->attrID );
    	  		*pBuf++ = HI_UINT16( writeStatus->attrID );
    		}
		}
		return buffer;
	}
}