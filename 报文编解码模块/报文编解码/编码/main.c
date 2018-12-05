#include"teacher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

	Teacher * t = (Teacher *)malloc(sizeof(Teacher));
	t->p = (char *)malloc(1024);
	memcpy(t->name, "pipi", sizeof("pipi"));
	t->age = 18;
	memcpy(t->p, "fghj170356", sizeof("fghj170356"));
	t->plen = 1;

	//±àÂë
	char * data;
	unsigned long len;
	encodeTeacher(t, &data, &len);
	printf("data:[%s]\nlen[%lu]\n", data, len);
	
	//½âÂë
	Teacher* pt;
	decodeTeacher(data, len, &pt);
	printf("name:	%s\n", pt->name);
	printf("age:	%d\n", pt->age);
	printf("p:	%s\n", pt->p);
	printf("plen:	%d\n", pt->plen);
	system("pause");
	return 0;
}


