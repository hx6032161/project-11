#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace::std;

class ListNode
{
public:
	ListNode();
	ListNode(char * data);
	~ListNode();

	char data[1024];
	ListNode * next;
};

class Mylist
{
public:
	Mylist();
	~Mylist();

	int addNode(char * data);
	int addNode(char * data, int location);
	int delLastNode();
	int reverseList();
	int printfList();
	
	ListNode * phead;
	int m_len;
};