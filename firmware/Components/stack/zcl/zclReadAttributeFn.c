/**************************************************************************************************

 DESCRIPTION:
  --

 CREATED: 30/10/2015, by Paolo Achdjian

 FILE: zclReadAttributeFn.c

***************************************************************************************************/

#include "zclReadAttributeFn.h"
#include "OSAL_Memory.h"

#define ZCL_STATUS_UNSUPPORTED_ATTRIBUTE                0x86

static struct ReadAttributeFnList * head;

static void readAttributeFnDefault(zclAttrRec_t *);

void addReadAttributeFn(uint8 endpoint, uint16 cluster, ReadAttributeFn callback){
	if (head == NULL){
		head = (struct ReadAttributeFnList *) osal_mem_alloc(sizeof(struct ReadAttributeFnList));
		head->endpoint = endpoint;
		head->clusterId = cluster;
		head->callback = callback;
		head->next = NULL;
	} else {
		struct ReadAttributeFnList * newHead = (struct ReadAttributeFnList *) osal_mem_alloc(sizeof(struct ReadAttributeFnList));
		newHead->endpoint = endpoint;
		newHead->clusterId = cluster;
		newHead->callback = callback;
		newHead->next = head;
		head = newHead;
	}
}

ReadAttributeFn findReadAttributeFn(uint8 endpoint, uint16 clusterId){
	struct ReadAttributeFnList * iter = head;
	while (iter != NULL){
		if (iter->endpoint == endpoint && clusterId == clusterId){
			return iter->callback;
		}
	}
	return &readAttributeFnDefault;
}

void readAttributeFnDefault(zclAttrRec_t * status){
	status->attr.status=ZCL_STATUS_UNSUPPORTED_ATTRIBUTE;
}