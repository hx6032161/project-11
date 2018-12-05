#include "teacher.h"
#include "itcast_asn1_der.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	typedef struct _Teacher
	{
		char name[64];
		int age;
		char *p;
		long plen;
	}Teacher;
*/


int encodeTeacher(Teacher * p, char ** outData, int * outlen)
{
	ITCAST_ANYBUF * head = NULL;
	ITCAST_ANYBUF * temp = NULL;
	ITCAST_ANYBUF * next = NULL;
	//编码name
	//ITCAST_INT DER_ITCAST_String_To_AnyBuf(ITCAST_ANYBUF **pOriginBuf, unsigned char * strOrigin, int strOriginLen);
	DER_ITCAST_String_To_AnyBuf(&temp, p->name, strlen(p->name)+1);
	//ITCAST_INT DER_ItAsn1_WritePrintableString(ITASN1_PRINTABLESTRING *pPrintString, ITASN1_PRINTABLESTRING **ppDerPrintString);
	DER_ItAsn1_WritePrintableString(temp, &head);
	//ITCAST_INT DER_ITCAST_FreeQueue(ITCAST_ANYBUF *pAnyBuf);
	DER_ITCAST_FreeQueue(temp);
	next = head;

	//编码age
	//ITCAST_INT DER_ItAsn1_WriteInteger(ITCAST_UINT32 integer, ITASN1_INTEGER **ppDerInteger);
	DER_ItAsn1_WriteInteger(p->age, &next->next);
	next = next->next;

	//编码p
	//int EncodeChar(char *pData, int dataLen, ITCAST_ANYBUF **outBuf);
	EncodeChar(p->p, strlen(p->p) + 1, &next->next);
	next = next->next;

	//编码plen
	DER_ItAsn1_WriteInteger(p->plen, &next->next);
	next = next->next;

	//序列化
	//ITCAST_INT DER_ItAsn1_WriteSequence(ITASN1_SEQUENCE *pSequence, ITCAST_ANYBUF **ppDerSequence);
	DER_ItAsn1_WriteSequence(head, &temp);

	//输出参数赋值
	*outData = temp->pData;
	*outlen = temp->dataLen;

	//free
	DER_ITCAST_FreeQueue(head);
	return 0;
}

/*
	typedef struct _Teacher
	{
		char name[64];
		int age;
		char *p;
		long plen;
	}Teacher;
*/

int decodeTeacher(char * inData, int inLen, Teacher ** p)
{
	ITCAST_ANYBUF * head = NULL;
	ITCAST_ANYBUF * temp = NULL;
	ITCAST_ANYBUF * next = NULL;

	Teacher * pt = (Teacher*)malloc(sizeof(Teacher));
	if (pt == NULL)
	{
		return -1;
	}
	//转换inData为anybuf
	DER_ITCAST_String_To_AnyBuf(&temp, inData, inLen);
	//将inData反序列化为链表
	DER_ItAsn1_ReadSequence(temp, &head);
	DER_ITCAST_FreeQueue(temp);
	//解码name
	//ITCAST_INT DER_ItAsn1_ReadPrintableString(ITASN1_PRINTABLESTRING *pDerPrintString, ITASN1_PRINTABLESTRING **ppPrintString);
	next = head;
	DER_ItAsn1_ReadPrintableString(next, &temp);
	memcpy(pt->name, temp->pData, temp->dataLen);
	DER_ITCAST_FreeQueue(temp);
	next = next->next;
	//解码age
	DER_ItAsn1_ReadInteger(next, &pt->age);
	next = next->next;
	//解码p
	int len = 0;
	DecodeChar(next, &pt->p, &len);
	next = next->next;
	//解码plen
	DER_ItAsn1_ReadInteger(next, &pt->plen);

	//输出参数赋值
	*p = pt;
	//free
	DER_ITCAST_FreeQueue(head);
	return 0;
}

void freeTeacher(Teacher ** p)
{
	if ((*p) != NULL)
	{
		if ((*p)->p != NULL)
		{
			free((*p)->p);
		}
		free(*p);
	}
}
