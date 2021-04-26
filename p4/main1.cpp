#include <iostream>
#include <cassert>
using namespace std;
//Получить символ, который повторяется наибольшее количества раз. Если
//таких несколько, то вернуть массив из этих символов (наследник) 

class MyString
{
protected:
    int Length;
    char* Str;

public:
    MyString()
    {
        Str = nullptr;
        Length = 0;
    }
    MyString(const char* ptr)
    {
        
        for (int i = 0;; i++)
        {
            if (ptr[i] == '\0')
            {
                Length = i;
                break;
            }

        }
        Str = new char[Length];
        for (int i = 0; i < Length; i++)
        {
            Str[i] = ptr[i];
        }
    }


    MyString(const MyString& other)
    {
        if (this != &other)
            {
            this->Length = other.Length;

            if (other.Str)
            {
                this->Str = new char[Length];


                for (int i = 0; i < Length; i++)
                {
                    this->Str[i] = other.Str[i];
                }
            }
        }
        
    }
    friend ostream& operator<<(std::ostream& out, const MyString& other) 
    {
        out << other.Str;
        return out;
    }
    MyString& operator = (const MyString& other)
    {
        if(this != &other)
        {
            this->Length = other.Length;
            if (this->Str != nullptr)
            {
                delete[] this->Str;
            }

            this->Str = new char[Length];
            for (int i = 0; i < Length; i++)
            {
                this->Str[i] = other.Str[i];
            }
        }

        return *this;
    }
    ~MyString()
    {
        if (Str != nullptr)
        {
            delete[] Str;
            Str = nullptr;
        }
    }
};
class ChildStr : public MyString
{
public:
    ChildStr() :MyString() {}
    ChildStr(const char* ptr) :MyString(ptr) {}
    ChildStr(const MyString& other) :MyString(other) {}

    char* MaxChar()
    {
        bool flag = false;
        int k = 0;
        int max = 0;
        char* ptr = new char [1];
        int lengthm = 1;
        int len = 0;
        for (int i = 0; i < this->Length; i++)
        {
            flag = false;
            k = 1;
            for (int j = 0; j < this->Length; j++)
            {
                if (i != j)
                {
                    if (Str[i] == Str[j])
                    {
                        k++;
                    }
                }
            }
            
            if (k > max)
            {
                len = 1;
                lengthm = 1;
                max = k;
                if (ptr != nullptr)
                {
                    delete[] ptr;
                    ptr = nullptr;
                }
                ptr = new char[2];
                ptr[1] = '\0';
                ptr[0] = Str[i];
            }
            else if (k == max)
            {
                for (int j = 0; j < lengthm; j++)
                {
                    if (Str[i] == ptr[j])
                        flag = true;
                }
                if (!flag)
                {
                    lengthm++;
                    char* tmp = new char[lengthm+1];
                    tmp[lengthm] = '\0';
                    for (int j = 0; j < lengthm; j++)
                    {
                        if (j != lengthm - 1)
                            tmp[j] = ptr[j];
                        else
                        {
                            tmp[j] = Str[i];
                        }
                    }
                    if (ptr != nullptr)
                    {
                        delete[] ptr;
                        ptr = nullptr;
                        len = 0;
                    }
                    len++;
                    ptr = tmp;
                }
            }
        }
        //cout<<sizeof(ptr)<< endl;
        return ptr;
    }

    ~ChildStr()
    {
        if (Str != nullptr)
        {
            delete[] Str;
            Str = nullptr;
        }
    }
};
int main()
{
    ChildStr x("sssss");

    cout << x.MaxChar();
    
}