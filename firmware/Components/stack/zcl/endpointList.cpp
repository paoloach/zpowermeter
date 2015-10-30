#include <stdlib.h>
#include "OSAL_Memory.h"
#include "endpointList.h"


EndpointList::EndpointList() {
	head=(EndpointList::Item *)NULL;
}

void EndpointList::add( unsigned char endpoint, CONST zclAttrRec_t  newAttrList[]) {
	EndpointList::Item * newItem = (EndpointList::Item *)osal_mem_alloc( sizeof( zclAttrRecsList ) );
	if ( newItem != NULL )  {
		newItem->next = head;
  		newItem->endpoint = endpoint;
		newItem->attrs = newAttrList;
		head = newItem;
 	}
}

const zclAttrRec_t  __code  * EndpointList::zclFindAttrRecsList( unsigned char endpoint ) {
	EndpointList::Item *pLoop = head;

	while ( pLoop != NULL ){
		if ( pLoop->endpoint == endpoint ) {
			return  pLoop->attrs; ;
    	}

    	pLoop = pLoop->next;
  	}

	return (const zclAttrRec_t  __code  *)NULL;
}