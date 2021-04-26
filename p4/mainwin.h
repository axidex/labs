#pragma once
#include <iostream>


using namespace std;

class MyString // мой класс
{
private: 
int Length;
char *Str;

public:
MyString();
MyString(const char *ptr);

MyString(const MyString &other);
const char* GetStr() const;
const int GetLength() const;
const int GetSize() const;
 MyString& operator = (const MyString &other);
bool operator == (const MyString &other);
bool operator != (const MyString &other);
void operator +=(const MyString &other);
friend std::ostream& operator<< (std::ostream &out, const MyString &other);


~MyString();

};


