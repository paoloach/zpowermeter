#ifndef __ZCL_PARSE_CMD__H__
#define __ZCL_PARSE_CMD__H__

#include "hal_types.h"

// Parse received command
struct zclParseCmd_t{
  uint8  endpoint;
  uint16 dataLen;
  uint8  *pData;
} ;

#endif