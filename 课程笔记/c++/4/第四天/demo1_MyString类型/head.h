#pragma once   //当前头文件只能被包含一次
#include <cstring>
#include <iostream>

using namespace std;

class MyString
{
private:
    int len;
    char *p;
    //friend void operator<<(ostream& out,MyString& obj);
    //friend ostream operator<<(ostream& out,MyString& obj);
    friend ostream& operator<<(ostream& out,MyString& obj);
public:
    MyString(const char *s);
    ~MyString();
    MyString(const MyString& obj);

    MyString& operator=(MyString& obj);

    char& operator[](int index);

    bool operator==(MyString& obj);
    bool operator==(const char *s);
};
