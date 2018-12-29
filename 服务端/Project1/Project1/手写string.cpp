#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace::std;

class Mystring
{
public:
	friend ostream& operator<<(ostream &out, Mystring &str);
	friend istream& operator>>(istream &in, Mystring &str);
public:
	Mystring();
	Mystring(const char * str);
	Mystring(Mystring &str);
	~Mystring();

	Mystring operator+(Mystring &str);
	Mystring operator+(char * str);

	Mystring& operator=(Mystring &str);
	Mystring& operator=(char * str);
private:
	char * m_str;
	int m_size;
	int m_capacity;
};

Mystring::Mystring()
{
	m_str = new char[10];
	memset(m_str, 0x00, 10);
	m_capacity = 10;
	m_size = 0;
}

Mystring::Mystring(const char * str)
{
	m_size = strlen(str);
	m_capacity = m_size;
	m_str = new char[m_size + 1];
	memset(m_str, 0x00, m_size + 1);
	//memcpy(m_str, str, m_size + 1);
	strcpy(m_str, str);
}

//拷贝构造函数
Mystring::Mystring(Mystring &str)
{
	cout << "拷贝构造函数调用" << endl;
	m_size = str.m_size;
	m_capacity = str.m_capacity;
	m_str = new char[m_size + 1];
	memcpy(m_str, str.m_str, m_size + 1);
}


Mystring::~Mystring()
{
	if (m_str != NULL)
	{
		delete m_str;
	}
}

Mystring Mystring::operator + (Mystring &str)
{
	char temp[1024] = { 0 };
	sprintf(temp, "%s%s", this->m_str, str.m_str);
	Mystring strnew(temp);
	return strnew;
}

Mystring Mystring::operator + (char * str)
{
	char temp[1024] = { 0 };
	sprintf(temp, "%s%s", this->m_str, str);
	Mystring strnew(temp);
	return strnew;
}

Mystring& Mystring::operator=(Mystring &str)
{
	char * temp = this->m_str;
	m_str = new char[strlen(str.m_str) + 1];
	strcpy(m_str, str.m_str);
	delete temp;
	m_size = strlen(str.m_str);
	m_capacity = m_size;
	return *this;
}
Mystring& Mystring::operator=(char * str)
{
	char * temp = this->m_str;
	m_str = new char[strlen(str) + 1];
	strcpy(m_str, str);
	delete temp;
	m_size = strlen(str);
	m_capacity = m_size;
	return *this;
}

ostream& operator<<(ostream &out, Mystring &str)
{
	out << str.m_str;
	return out;
}

istream & operator>>(istream &in, Mystring &str)
{
	char temp[1024] = { 0 };
	in >> temp;
	strncpy(str.m_str, temp, str.m_capacity - 1);
	return in;
}

int main01()
{
	Mystring a;
	Mystring b("111");
	Mystring c("abd");
	a = b + c + c + c;
	cout << a << endl;

	system("pause");
	return 0;
}