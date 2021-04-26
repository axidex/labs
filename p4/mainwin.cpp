#include "mainwin.h"
#include <iostream>


using namespace std;



MyString::MyString()
{
  Str = nullptr;
  Length = 0;
}
MyString::MyString(const char *ptr)
{
  for (int i = 0 ;;i++)
  {
    if(ptr[i] == '\0')
    {
      Length = i;
      break;
    }

  }
  Str = new char[Length];
  for (int i = 0;i< Length;i++)
  {
    Str[i]=ptr[i];
  } 
}


MyString::MyString(const MyString &other)
{
  this->Length = other.Length;

  if (other.Str)
  {
    this->Str = new char[Length];


    for (int i = 0;i<Length;i++)
    {
      this->Str[i] = other.Str[i];
    }
  }
}
MyString& MyString:: operator = (const MyString &other)
{
  this->Length=other.Length;
  if (this->Str != nullptr)
  {
    delete[] this->Str;
  }
  
  this->Str = new char[Length];
  for (int i = 0;i<Length;i++)
  {
    this->Str[i]=other.Str[i];
  }
  
  return *this;
}

bool MyString::operator == (const MyString &other)
{
  if (this->Length != other.Length)
  {
    return false;
  }
  else
  {
    for (int i = 0 ; i < this->Length;i++)
    {
      if (this->Str[i] != other.Str[i])
      {
        return false ;
            
      }

    }
    return true;
  }
}
bool MyString::operator != (const MyString &other)
{
  return !(*this==other); 
}
void MyString::operator +=(const MyString &other)
{
  int j = 0;
  int temp =  this->Length ;
  this->Length+=other.Length ;
  char *tempo ;
  tempo = new char [temp];
  for (int i = 0;i<temp;i++)
  {
    tempo[i] = this->Str[i];
  }

  if (this->Str != nullptr)
  {
    delete[] this->Str;
  }
  this->Str = new char [Length];
  for (int i = 0;i<temp;i++)
  {
    this->Str[i] = tempo[i];
  }
  
  for (int i = temp;i<Length;i++)
  { 
    
    this->Str[i]= other.Str[j];
    j++;
    
  }
  
  
  delete[] tempo;
  tempo = nullptr;  
}
const char* MyString::GetStr() const
{
  return Str;
}
ostream & operator<<(std::ostream &out, const MyString &other)
{
    out << other.Str;
    return out;
}
const int MyString::GetLength() const 
{
  return Length;
}
const int MyString::GetSize() const 
{
  return Length+1;
}
MyString::~MyString()
{
  delete[] Str;
  Str = nullptr;
}

