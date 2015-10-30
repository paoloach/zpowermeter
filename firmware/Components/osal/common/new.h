#ifndef __NEW__H__
#define __NEW__H__

#include "OSAL_Memory.h"

void * operator new(unsigned int size) {
	return osal_mem_alloc(size);
}
#endif