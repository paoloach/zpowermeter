#include "AttributeUtils.h"
#include "hal_defs.h"
#include "ssp.h"
#include "OSAL.h"

/*********************************************************************
 * @fn      zclGetAttrDataLength
 *
 * @brief   Return the length of the attribute.
 *
 * @param   dataType - data type
 * @param   pData - pointer to data
 *
 * @return  returns atrribute length
 */
uint16 zclGetAttrDataLength( uint8 dataType, uint8 *pData ){
	uint16 dataLen = 0;

	if ( dataType == ZCL_DATATYPE_LONG_CHAR_STR || dataType == ZCL_DATATYPE_LONG_OCTET_STR ){
		dataLen = BUILD_UINT16( pData[0], pData[1] ) + 2; // long string length + 2 for length field
	} else if ( dataType == ZCL_DATATYPE_CHAR_STR || dataType == ZCL_DATATYPE_OCTET_STR ) {
		dataLen = *pData + 1; // string length + 1 for length field
	} else {
		dataLen = zclGetDataTypeLength( dataType );
	}

	return ( dataLen );
}

/*********************************************************************
 * @fn      zclGetDataTypeLength
 *
 * @brief   Return the length of the datatype in octet.
 *
 *          NOTE: Should not be called for ZCL_DATATYPE_OCTECT_STR or
 *                ZCL_DATATYPE_CHAR_STR data types.
 *
 * @param   dataType - data type
 *
 * @return  length of data
 */
uint8 zclGetDataTypeLength( uint8 dataType ){
	uint8 len;

	switch ( dataType ) {
    case ZCL_DATATYPE_DATA8:
    case ZCL_DATATYPE_BOOLEAN:
    case ZCL_DATATYPE_BITMAP8:
    case ZCL_DATATYPE_INT8:
    case ZCL_DATATYPE_UINT8:
    case ZCL_DATATYPE_ENUM8:
      len = 1;
      break;

    case ZCL_DATATYPE_DATA16:
    case ZCL_DATATYPE_BITMAP16:
    case ZCL_DATATYPE_UINT16:
    case ZCL_DATATYPE_INT16:
    case ZCL_DATATYPE_ENUM16:
    case ZCL_DATATYPE_SEMI_PREC:
    case ZCL_DATATYPE_CLUSTER_ID:
    case ZCL_DATATYPE_ATTR_ID:
      len = 2;
      break;

    case ZCL_DATATYPE_DATA24:
    case ZCL_DATATYPE_BITMAP24:
    case ZCL_DATATYPE_UINT24:
    case ZCL_DATATYPE_INT24:
      len = 3;
      break;

    case ZCL_DATATYPE_DATA32:
    case ZCL_DATATYPE_BITMAP32:
    case ZCL_DATATYPE_UINT32:
    case ZCL_DATATYPE_INT32:
    case ZCL_DATATYPE_SINGLE_PREC:
    case ZCL_DATATYPE_TOD:
    case ZCL_DATATYPE_DATE:
    case ZCL_DATATYPE_UTC:
    case ZCL_DATATYPE_BAC_OID:
      len = 4;
      break;

   case ZCL_DATATYPE_UINT40:
   case ZCL_DATATYPE_INT40:
       len = 5;
       break;

   case ZCL_DATATYPE_UINT48:
   case ZCL_DATATYPE_INT48:
       len = 6;
       break;

   case ZCL_DATATYPE_UINT56:
   case ZCL_DATATYPE_INT56:
       len = 7;
       break;

   case ZCL_DATATYPE_DOUBLE_PREC:
   case ZCL_DATATYPE_IEEE_ADDR:
   case ZCL_DATATYPE_UINT64:
   case ZCL_DATATYPE_INT64:
     len = 8;
     break;

    case ZCL_DATATYPE_128_BIT_SEC_KEY:
     len = SEC_KEY_LEN;
     break;

    case ZCL_DATATYPE_NO_DATA:
    case ZCL_DATATYPE_UNKNOWN:
      // Fall through

    default:
      len = 0;
      break;
  	}

	return len ;
}

/*********************************************************************
 * @fn      zclSerializeData
 *
 * @brief   Builds a buffer from the attribute data to sent out over
 *          the air.
 *          NOTE - Not compatible with application's attributes callbacks.
 *
 * @param   dataType - data types defined in zcl.h
 * @param   attrData - pointer to the attribute data
 * @param   buf - where to put the serialized data
 *
 * @return  pointer to end of destination buffer
 */
uint8 *zclSerializeData( uint8 dataType, void *attrData, uint8 *buf ){
  uint8 *pStr;
  uint16 len;

  if ( attrData == NULL )
  {
    return ( buf );
  }

  switch ( dataType )
  {
    case ZCL_DATATYPE_DATA8:
    case ZCL_DATATYPE_BOOLEAN:
    case ZCL_DATATYPE_BITMAP8:
    case ZCL_DATATYPE_INT8:
    case ZCL_DATATYPE_UINT8:
    case ZCL_DATATYPE_ENUM8:
      *buf++ = *((uint8 *)attrData);
       break;

    case ZCL_DATATYPE_DATA16:
    case ZCL_DATATYPE_BITMAP16:
    case ZCL_DATATYPE_UINT16:
    case ZCL_DATATYPE_INT16:
    case ZCL_DATATYPE_ENUM16:
    case ZCL_DATATYPE_SEMI_PREC:
    case ZCL_DATATYPE_CLUSTER_ID:
    case ZCL_DATATYPE_ATTR_ID:
      *buf++ = LO_UINT16( *((uint16*)attrData) );
      *buf++ = HI_UINT16( *((uint16*)attrData) );
      break;

    case ZCL_DATATYPE_DATA24:
    case ZCL_DATATYPE_BITMAP24:
    case ZCL_DATATYPE_UINT24:
    case ZCL_DATATYPE_INT24:
      *buf++ = BREAK_UINT32( *((uint32*)attrData), 0 );
      *buf++ = BREAK_UINT32( *((uint32*)attrData), 1 );
      *buf++ = BREAK_UINT32( *((uint32*)attrData), 2 );
      break;

    case ZCL_DATATYPE_DATA32:
    case ZCL_DATATYPE_BITMAP32:
    case ZCL_DATATYPE_UINT32:
    case ZCL_DATATYPE_INT32:
    case ZCL_DATATYPE_SINGLE_PREC:
    case ZCL_DATATYPE_TOD:
    case ZCL_DATATYPE_DATE:
    case ZCL_DATATYPE_UTC:
    case ZCL_DATATYPE_BAC_OID:
      buf = osal_buffer_uint32( buf, *((uint32*)attrData) );
      break;

    case ZCL_DATATYPE_UINT40:
      pStr = (uint8*)attrData;
      buf = (unsigned char *)osal_memcpy( buf, pStr, 5 );
      break;

    case ZCL_DATATYPE_UINT48:
      pStr = (uint8*)attrData;
      buf = (unsigned char *)osal_memcpy( buf, pStr, 6 );
      break;

    case ZCL_DATATYPE_IEEE_ADDR:
      pStr = (uint8*)attrData;
      buf = (unsigned char *)osal_memcpy( buf, pStr, 8 );
      break;

    case ZCL_DATATYPE_CHAR_STR:
    case ZCL_DATATYPE_OCTET_STR:
      pStr = (uint8*)attrData;
      len = *pStr;
      buf = (unsigned char *)osal_memcpy( buf, pStr, len+1 ); // Including length field
      break;

    case ZCL_DATATYPE_LONG_CHAR_STR:
    case ZCL_DATATYPE_LONG_OCTET_STR:
      pStr = (uint8*)attrData;
      len = BUILD_UINT16( pStr[0], pStr[1] );
      buf = (unsigned char *)osal_memcpy( buf, pStr, len+2 ); // Including length field
      break;

    case ZCL_DATATYPE_128_BIT_SEC_KEY:
      pStr = (uint8*)attrData;
      buf = (unsigned char *)osal_memcpy( buf, pStr, SEC_KEY_LEN );
      break;

    case ZCL_DATATYPE_NO_DATA:
    case ZCL_DATATYPE_UNKNOWN:
      // Fall through

    default:
      break;
  }

  return ( buf );
}

