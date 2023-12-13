#include <iostream>
#include <stdio.h>
using namespace std;

class hstring
{
	char* buf;
	unsigned short value_len;
	unsigned short length(const char* str)
	{
		unsigned short len{};
		while (str[len++]);
		return len;
	}
public:

	hstring() {
		buf = new char[1024];
	}
	/*
		常规构造函数 ↓
	*/
	hstring(const char* value) {
		buf = new char[1024];
		value_len = length(value);
		memcpy(buf,value,value_len);
	}
	/*
		拷贝构造函数 ↓
	*/
	hstring(const hstring& Other) :hstring(Other.Get())
	{
	}
	/*
		获得当前的缓冲区的值 ↓
	*/
	char* Get()  const
	{
		return buf;
	}
	/*
		设置当前的缓冲区的值 ↓
	*/
	char* Set(const char* value) 
	{
		value_len = length(value);
		memcpy(buf,value,value_len);
	}
	hstring operator+(const char* pOther)
	{
		memcpy(buf,pOther,sizeof(pOther));
		return buf;
	}
	hstring operator=(const char* pOther)
	{
		memcpy(buf, pOther, sizeof(pOther));
		return buf;
	}

	~hstring()
	{
		delete[] buf;
	}
};
//unit test
int main() {
	hstring my_string{"hello"};
	hstring str{ my_string };
	cout << (char*)str.Get() << endl;
}