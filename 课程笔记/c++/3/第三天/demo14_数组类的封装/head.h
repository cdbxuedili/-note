#pragma once
#include <cstdio>
class MyArray
{
private:
    int len;
    int *p;

public:
    MyArray(int len);
    ~MyArray();

    void setvalue(int index,int data);
    int getvalue(int index);
    int getlen();

public:
    int& operator[](int index);
    MyArray(const MyArray& obj);
    MyArray operator=(MyArray& obj);
};


