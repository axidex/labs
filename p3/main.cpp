//вариант 7
//задание 3
/*
Необходимо реализовать указанную схему наследования. В схеме «0» А1 –
родитель для классов B1, B2.
1 Каждый класс содержит защищённую переменную. Например: A1
содержит переменную a1, B1 – b1, C2 – c2 и т.п. Каждый класс имеет
конструктор, присваивающий этой переменной некое значение.
Конструкторы производных классов должны вызывать конструкторы
базовых классов и передавать туда параметры.
2 В базовых классах реализовать функцию print(), которая выводит на
консоль имя класса, из которого она вызвана. В производных классах
переопределять её, чтобы она выводила корректный результат.
Например:
A1 a;
a.print(); => “A1”
B1 b;
b.print(); => “B1”
3 Написать функцию show(), которая выводит все доступные для этого
класса переменные. Например, в классе B1 доступны локальные
переменные класса B1 и некоторые переменные из родительского
класса A1. Переопределить её в производных классах.
A1 a;
a.show(); => только переменные в A1
B1 b;
b.show(); => переменные из B1 и A1
*/
#include <iostream>
using namespace std;
class A1
{
protected:
    int a1;

public:
    A1(int V1 = 0)
    {
        a1 = V1;
        cout << "\nClass A1 constructor";
    }
    virtual void print() { cout << "\nVariable of A1 class"; }
    virtual void show() { cout << "\na1 = " << a1; }
};
class A2
{
protected:
    int a2;
public:
    A2(int V1 = 0)
        {
            a2 = V1;
            cout << "\nClass A2 constructor";
        }
        virtual void print() { cout << "\nVariable of A2 class"; }
        virtual void show() { cout << "\na2 = " << a2; }
} ;
class A3
{
protected:
    int a3;

public:
    A3(int V1 = 0)
    {
        a3 = V1;
        cout << "\nClass A3 constructor";
    }
    virtual void print() { cout << "\nVariable of A3 class"; }
    virtual void show() { cout << "\na3 = " << a3 ; }
};
class B1 : virtual public A1,virtual public A2,virtual public A3
{
protected:
    int b1;

public:
    B1(int V1 = 0, int V2 = 0,int V3 = 0, int V4 = 0) : A1(V2),A2(V3),A3(V4)
    {
        b1 = V1;
        cout << "\nClass B1 constructor";
    }
    virtual void print() { cout << "\nVariable of B1 class"; }
    virtual void show() { cout << "\nb1 = " << b1 << ", a1 = " << a1<< ", a2 = " << a2 << ", a3 = " << a3; }
};
class B2 : virtual public A1,virtual public A2,virtual public A3
{
protected:
    int b2;

public:
    B2(int V1 = 0, int V2 = 0,int V3 = 0, int V4 = 0) : A1(V2),A2(V3),A3(V4)
    {
        b2 = V1;
        cout << "\nClass B2 constructor";
    }
    virtual void print() { cout << "\nVariable of B2 class"; }
    virtual void show() { cout << "\nb2 = " << b2 << ", a1 = " << a1<< ", a2 = " << a2 << ", a3 = " << a3; }
};
class C1 : virtual public B1,virtual public B2
{
protected:
    int c1;

public:
    C1(int V1 = 0, int V2 = 0,int V3 = 0, int V4 = 0,int V5 = 0, int V6 = 0) : A1(V2),A2(V3),A3(V4),B1(V5),B2(V6)
    {
        c1 = V1;
        cout << "\nClass C1 constructor";
    }
    virtual void print() { cout << "\nVariable of C1 class"; }
    virtual void show() { cout <<", c1 = " << c1 << ", b1 = " << b1<< "\nb2 = " << b2 << ", a1 = " << a1<< ", a2 = " << a2 << ", a3 = " << a3; }
};
int main()
{
    C1 test(1, 2);
    test.show();
    test.print();
    A1 *ptr = &test;
    ptr->show();
    ptr->print();
    char c;
    std::cin >> c;
    return 0;
}