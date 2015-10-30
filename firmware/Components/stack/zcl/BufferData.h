#ifndef __BUFFER_DATA__H__
#define __BUFFER_DATA__H__

#include "OSAL_Memory.h"

class BufferData {
public:
	BufferData(){
		data=NULL;
		dataLen=0;
	}
	
	BufferData(const BufferData & a){
		data = a.data;
		dataLen = a.dataLen;
		a.data=NULL;
		a.dataLen=0;
	}
	BufferData(uint16 dataLen){
		data = new unsigned char[dataLen];
		this->dataLen = dataLen;
	}
	~BufferData() {
		delete data;
	}
	bool isValid(){
		return data != NULL;
	}
	mutable uint16 dataLen;
	mutable unsigned char * data;
};

#endif