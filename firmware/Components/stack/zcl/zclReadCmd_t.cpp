

#include "zclReadCmd_t.h"
#include "OSAL_Memory.h"
#include "hal_defs.h"

zclReadCmd_t::zclReadCmd_t(zclParseCmd_t * pCmd){
	uint8 *pBuf = pCmd->pData;

	attrID = (uint16 *)osal_mem_alloc( pCmd->dataLen );
	uint8 i;
	numAttr = pCmd->dataLen / 2; // Atrribute ID
	for ( i = 0; i < numAttr; i++ ) {
		attrID[i] = BUILD_UINT16( pBuf[0], pBuf[1] );
		pBuf += 2;
	}
}

BufferData zclReadCmd_t::getBufferFromAttribute() {
	uint16 dataLen = numAttr * 2; // Attribute ID
	BufferData buffer(dataLen);
	if ( buffer.isValid() ){
		uint8 i;

		uint8 *pBuf = buffer.data;
    	for (i = 0; i < numAttr; i++) {
      		*pBuf++ = LO_UINT16( attrID[i] );
      		*pBuf++ = HI_UINT16( attrID[i] );
    	}
	}
	return buffer;
}