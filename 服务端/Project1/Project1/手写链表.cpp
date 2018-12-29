#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"MyList.h"
using namespace::std;


int main02()
{
	Mylist mylist;
	mylist.addNode("123");
	mylist.addNode("456");
	mylist.addNode("789");
	mylist.addNode("---", 0);
	mylist.delLastNode();
	mylist.reverseList();
	mylist.printfList();
	system("pause");
	return 0;
}