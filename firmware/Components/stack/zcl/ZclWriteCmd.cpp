#include "ZclWriteCmd.h"
#include "AttributeUtils.h"
#include "hal_defs.h"
#include "osal.h"

#define PADDING_NEEDED( bufLen )    ( (bufLen) % 2 )

ZclWriteCmd::ZclWriteCmd(zclParseCmd_t *pCmd ){
	uint8 *pBuf = pCmd->pData;
	uint16 attrDataLen;
	uint8 numAttr = 0;
	ZclWriteRec * attributes;

  // find out the number of attributes and the length of attribute data
	while ( pBuf < ( pCmd->pData + pCmd->dataLen ) ){
		uint8 dataType;

		numAttr++;
		pBuf += 2; 
		dataType = *pBuf++;
		attrDataLen = zclGetAttrDataLength( dataType, pBuf );
		pBuf += attrDataLen; // move pass attribute data

		// add padding if needed
		if ( PADDING_NEEDED( attrDataLen ) ){
			attrDataLen++;
		}
	}

	attributes = new ZclWriteRec[numAttr];
	attrList = attributes;

	if ( attrList != NULL ){
		uint8 i;
		pBuf = pCmd->pData;
	    this->numAttr = numAttr;
    	for ( i = 0; i < numAttr; i++ ) {
     		attributes->attrID = BUILD_UINT16( pBuf[0], pBuf[1] );
      		pBuf += 2;
      		attributes->dataType = *pBuf++;

      		attrDataLen = zclGetAttrDataLength( attributes->dataType, pBuf );
			uint8 * dataPtr = new uint8[attrDataLen];
      		osal_memcpy( dataPtr, pBuf, attrDataLen);
      		attributes->attrData = dataPtr;

      		pBuf += attrDataLen; 

      		// advance attribute data pointer
      		if ( PADDING_NEEDED( attrDataLen ) ) {
        		attrDataLen++;
      		}
			attributes++;
    	}
  	}
}

ZclWriteCmd::~ZclWriteCmd(){
	if (attrList != NULL){
		ZclWriteRec * attributes = attrList;
		for(int i=0; i< numAttr; i++){
			delete attributes->attrData;
			attributes++;
		}
		delete attrList;
	}
}

uint16 ZclWriteCmd::getDataLen() {
	ZclWriteRec * attributes = attrList;
	uint16 dataLen=0;
	for(int i=0; i< numAttr; i++){
		dataLen += attributes->getDataLen();
		attributes++;
	}
	return dataLen;
}

BufferData ZclWriteCmd::getBufferFromAttribute(){
	uint16 dataLen = getDataLen();
	BufferData buffer(dataLen);
	
	 // Load the buffer - serially
    
	if (buffer.isValid()){
		ZclWriteRec * attributes = attrList;
		uint8 *pBuf = buffer.data;
    	for ( int i = 0; i < numAttr; i++ ){
	    	*pBuf++ = LO_UINT16( attributes->attrID );
      		*pBuf++ = HI_UINT16( attributes->attrID );
      		*pBuf++ = attributes->dataType;
		    pBuf = zclSerializeData( attributes->dataType, attributes->attrData, pBuf );
		}
    }

	return buffer;
}