#ifndef _TEACHER_H
#define _TEACHER_H
typedef struct _Teacher
{
	char name[64]; 
	int age;   
	char *p;
	long plen;
}Teacher;

// 编码结构体
//编码结构体
//p：输入参数 待编码的数据
//outdata：输出参数 编码后的数据
//outlen： 输出参数 outdata的长度
int encodeTeacher(Teacher* p, char** outData, int* outlen);
// 解码结构体
//解码结构体
//inData：输入参数 待解码的数据
//intLen：输入参数 inData的长度
//p： 输出参数 解码后的数据
int decodeTeacher(char* inData, int inLen, Teacher**p);
// 释放内存函数
void freeTeacher(Teacher** p);

#endif	// _TEACHER_H
