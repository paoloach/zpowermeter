/**************************************************************************************************

 DESCRIPTION:
  --

 CREATED: 23/10/2015, by Paolo Achdjian

 FILE: zclListAttribute.c

***************************************************************************************************/


#include "zclListAttribute.h"
#include "hal_types.h"
#include "OSAL_Memory.h"

#ifdef __cplusplus
extern "C"
{
#endif
	
static struct zclAttrRecsList *attrList = (struct zclAttrRecsList *)NULL;

static struct zclAttrRecsList *zclFindAttrRecsList( uint8 endpoint );

uint8_t zclFindAttrRec( uint8_t endpoint, uint16_t clusterID, uint16_t attrId, struct zclAttrRec_t *pAttr ){
	struct zclAttrRecsList * endpointList = zclFindAttrRecsList(endpoint);
	if(endpointList == NULL){
		return 0;
	}
	const struct  zclAttrRec_t __code  *iter = endpointList->attrs;
	for(; iter->clusterID != 0 || iter->attr.attrId !=0; iter++){
		if (iter->clusterID == clusterID && iter->attr.attrId==attrId){
			pAttr->clusterID = clusterID;
			pAttr->attr.accessControl = iter->attr.accessControl;
			pAttr->attr.attrId = attrId;
			pAttr->attr.dataPtr = iter->attr.dataPtr;
			pAttr->attr.dataType = iter->attr.dataType;
			pAttr->attr.writeCB = iter->attr.writeCB;
			return 1;
		}
	}
	return 0;
}

static struct zclAttrRecsList *zclFindAttrRecsList( uint8 endpoint ){
	struct zclAttrRecsList *pLoop = attrList;

	while ( pLoop != NULL ){
		if ( pLoop->endpoint == endpoint ) {
			return  pLoop ;
    	}

    	pLoop = pLoop->next;
  	}

	return ( NULL );
}

extern void zcl_registerAttrList(unsigned char endpoint, CONST struct zclAttrRec_t newAttrList[]){
	struct zclAttrRecsList * newItem = (struct  zclAttrRecsList*)osal_mem_alloc( sizeof( struct  zclAttrRecsList ) );
	if ( attrList != NULL )  {
		attrList->next = newItem;
  		attrList->endpoint = endpoint;
		attrList->attrs = newAttrList;
		attrList = newItem;
 	}
}

#ifdef __cplusplus
}
#endif