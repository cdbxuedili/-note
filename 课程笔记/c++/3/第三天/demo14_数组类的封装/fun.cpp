#include "head.h"

MyArray::MyArray(int len)
{
    this->len = len;
    this->p = new int[len];
}

MyArray::~MyArray()
{
    delete[] this->p;
    this->p = NULL;
    this->len = 0;
}

void MyArray::setvalue(int index,int data)
{
    this->p[index] = data;
}

int MyArray::getvalue(int index)
{
    return this->p[index];
}

int MyArray::getlen()
{
    return this->len;
}

int& MyArray::operator[](int index)
{
    return this->p[index];
}

MyArray::MyArray(const MyArray& obj)
{
    this->len = obj.len;
    this->p = new int [this->len];

    for(int i = 0;i < obj.len;i ++)
    {
        this->p[i] = obj.p[i];
    }
}

 MyArray MyArray::operator=(MyArray& obj)
{
    this->len = obj.len;
    this->p = new int [this->len];

    for(int i = 0;i < obj.len;i ++)
    {
        this->p[i] = obj.p[i];
    }

    return *this;
}
