

#include "OSAL_Memory.h"

void * operator new(unsigned int size) {
	return osal_mem_alloc(size);
}

void * operator new[](unsigned int size) {
	return osal_mem_alloc(size);
}

void  operator delete(void * pointer) {
	if (pointer != NULL){
		osal_mem_free(pointer);
	}
}

void  operator delete[](void * pointer) {
	if (pointer != NULL){
		osal_mem_free(pointer);
	}
}