#include "head.h"
MyString::MyString(const char *s) //还是属于类的内部，非内联函数
{
    if(s == NULL)
    {
        this->len = 0;
        this->p = new char [this->len + 1];
        strcpy(this->p,"");
    }
    else
    {
        this->len = strlen(s);
        this->p = new char[this->len + 1];//深拷贝
        //this->p = s;//浅拷贝
        strcpy(this->p,s);
    }
}

MyString::~MyString()
{
    delete[] this->p;
    this->p = NULL;
    this->len = 0;
}

MyString::MyString(const MyString& obj)
{
    if(obj.p == NULL)
    {
        this->len = 0;
        this->p = new char [this->len + 1];
        strcpy(this->p,"");
    }
    else
    {
        this->len = obj.len;
        this->p = new char [this->len + 1];
        strcpy(this->p,obj.p);
    }
}

MyString& MyString::operator=(MyString& obj)
{
    if(obj.p == NULL)
    {
        this->len = 0;
        this->p = new char [this->len + 1];
        strcpy(this->p,"");
    }
    else
    {
        this->len = obj.len;
        this->p = new char [this->len + 1];
        strcpy(this->p,obj.p);
    }

    return *this;
}

//void operator<<(ostream& out,MyString& obj)
//ostream operator<<(ostream& out,MyString& obj)//出错，返回了备份，并且调用了私有属性
ostream& operator<<(ostream& out,MyString& obj)
{
    out << obj.p;
    return out;
}


char& MyString::operator[](int index)
{
    return this->p[index];
}

bool MyString::operator==(MyString& obj)
{
    if(strcmp(this->p,obj.p) == 0)
        return true;
    else
        return false;
}

bool MyString::operator==(const char *s)
{
    if(strcmp(this->p,s) == 0)
        return true;
    else
        return false;
}
