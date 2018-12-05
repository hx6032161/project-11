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
	//����name
	//ITCAST_INT DER_ITCAST_String_To_AnyBuf(ITCAST_ANYBUF **pOriginBuf, unsigned char * strOrigin, int strOriginLen);
	DER_ITCAST_String_To_AnyBuf(&temp, p->name, strlen(p->name)+1);
	//ITCAST_INT DER_ItAsn1_WritePrintableString(ITASN1_PRINTABLESTRING *pPrintString, ITASN1_PRINTABLESTRING **ppDerPrintString);
	DER_ItAsn1_WritePrintableString(temp, &head);
	//ITCAST_INT DER_ITCAST_FreeQueue(ITCAST_ANYBUF *pAnyBuf);
	DER_ITCAST_FreeQueue(temp);
	next = head;

	//����age
	//ITCAST_INT DER_ItAsn1_WriteInteger(ITCAST_UINT32 integer, ITASN1_INTEGER **ppDerInteger);
	DER_ItAsn1_WriteInteger(p->age, &next->next);
	next = next->next;

	//����p
	//int EncodeChar(char *pData, int dataLen, ITCAST_ANYBUF **outBuf);
	EncodeChar(p->p, strlen(p->p) + 1, &next->next);
	next = next->next;

	//����plen
	DER_ItAsn1_WriteInteger(p->plen, &next->next);
	next = next->next;

	//���л�
	//ITCAST_INT DER_ItAsn1_WriteSequence(ITASN1_SEQUENCE *pSequence, ITCAST_ANYBUF **ppDerSequence);
	DER_ItAsn1_WriteSequence(head, &temp);

	//���������ֵ
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
	//ת��inDataΪanybuf
	DER_ITCAST_String_To_AnyBuf(&temp, inData, inLen);
	//��inData�����л�Ϊ����
	DER_ItAsn1_ReadSequence(temp, &head);
	DER_ITCAST_FreeQueue(temp);
	//����name
	//ITCAST_INT DER_ItAsn1_ReadPrintableString(ITASN1_PRINTABLESTRING *pDerPrintString, ITASN1_PRINTABLESTRING **ppPrintString);
	next = head;
	DER_ItAsn1_ReadPrintableString(next, &temp);
	memcpy(pt->name, temp->pData, temp->dataLen);
	DER_ITCAST_FreeQueue(temp);
	next = next->next;
	//����age
	DER_ItAsn1_ReadInteger(next, &pt->age);
	next = next->next;
	//����p
	int len = 0;
	DecodeChar(next, &pt->p, &len);
	next = next->next;
	//����plen
	DER_ItAsn1_ReadInteger(next, &pt->plen);

	//���������ֵ
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
