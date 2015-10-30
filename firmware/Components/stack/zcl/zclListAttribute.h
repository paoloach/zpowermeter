#ifndef __ZCL_LIST_ATTRIBUTES__H__
#define __ZCL_LIST_ATTRIBUTES__H__

#include "zcl_clusterDef.h"

#ifdef __cplusplus
extern "C"
{
#endif
	
typedef void (*AttributeWriteCB)(void);

typedef signed   char   int8_t;
typedef unsigned char   uint8_t;

typedef signed   short  int16_t;
typedef unsigned short  uint16_t;
// Attribute record
class zclAttribute_t{
public:
  uint16_t  attrId;         // Attribute ID
  uint8_t   dataType;       // Data Type - defined in AF.h
  uint8_t   accessControl;  // Read/write - bit field
  void    *dataPtr;       // Pointer to data field
  AttributeWriteCB writeCB; // The callback called when write attribute command is received for that attribute
} ;

struct zclAttrRec_t {
  uint16_t          clusterID;    // Real cluster ID
  struct zclAttribute_t  attr;
} ;


// Attribute record list item
struct zclAttrRecsList {
  struct zclAttrRecsList *next;
  uint8_t                  endpoint;      // Used to link it into the endpoint descriptor
  const struct  zclAttrRec_t __code     *attrs;        // attribute records
};

extern uint8_t zclFindAttrRec( uint8_t endpoint, uint16_t realClusterID, uint16_t attrId, struct zclAttrRec_t *pAttr );
extern void zcl_registerAttrList(unsigned char endpoint, CONST struct  zclAttrRec_t newAttrList[]);

#ifdef __cplusplus
}
#endif

#endif