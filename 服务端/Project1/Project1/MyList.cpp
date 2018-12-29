#include"MyList.h"

ListNode::ListNode()
{
	this->next = NULL;
	memset(this->data, 0x00, 1024);
}
ListNode::ListNode(char * data)
{
	this->next = NULL;
	memcpy(this->data, data, strlen(data));
}
ListNode::~ListNode()
{

}
Mylist::Mylist()
{
	this->phead = new ListNode();
	this->m_len = 0;
}
Mylist::~Mylist()
{
	if (NULL != this->phead)
	{
		delete this->phead;
	}
}


int Mylist::addNode(char * data)
{
	ListNode * newNode = new ListNode(data);
	ListNode * ptemp = NULL;
	ptemp = this->phead;
	while (NULL != ptemp->next)
	{
		ptemp = ptemp->next;
	}
	ptemp->next = newNode;
	this->m_len++;
	return 0;
}
int Mylist::addNode(char * data, int location)
{
	ListNode * newNode = new ListNode(data);
	ListNode * ptemp = NULL;
	ListNode * pnext = NULL;
	ptemp = this->phead;
	pnext = ptemp->next;
	for (int i = 0; i < location; i++)
	{
		ptemp = ptemp->next;
		pnext = ptemp->next;
	}
	ptemp->next = newNode;
	newNode->next = pnext;
	this->m_len++;
	return 0;
}
int Mylist::delLastNode()
{
	ListNode * ptemp = NULL;
	ListNode * pnext = NULL;
	ptemp = this->phead;
	pnext = ptemp->next;
	while (NULL != pnext->next)
	{
		ptemp = ptemp->next;
		pnext = ptemp->next;
	}
	delete pnext;
	ptemp->next = NULL;
	this->m_len--;
	return 0;
}
int Mylist::reverseList()
{	
	ListNode * ptemp = NULL;
	ListNode * pnext = NULL;
	ListNode * plast = NULL;
	ptemp = this->phead;
	pnext = ptemp->next;
	plast = pnext->next;
	pnext->next = NULL;
	while (NULL != plast)
	{
		ptemp = pnext;
		pnext = plast;
		plast = plast->next;
		pnext->next = ptemp;
	}
	this->phead->next = pnext;
	return 0;
}

int Mylist::printfList()
{
	ListNode * ptemp = NULL;
	ptemp = this->phead;
	while (NULL != ptemp->next)
	{
		ptemp = ptemp->next;
		cout << ptemp->data << endl;
	}
	return 0;
}
