#ifndef __ENDPOINT_LIST__H__
#define __ENDPOINT_LIST__H__

#include "zclListAttribute.h"

class EndpointList {
private:
	class Item {
	public:
		Item * next;
		unsigned char endpoint;
		const zclAttrRec_t  __code * attrs;
	};
	
	Item * head;
	
public:
	EndpointList();
	void add( unsigned char endpoint, CONST zclAttrRec_t newAttrList[]);
	const zclAttrRec_t  __code  *zclFindAttrRecsList( unsigned char endpoint );
};

#endif