#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<cassert>

using namespace std;

struct Stadium
{
    Stadium()
    {
        Name = "Null";
        Sport = "Null";
        Year = rand() % 70 + 1950;
        Watchers = rand() % 10000 + 5000;
        NumArena = rand() % 20 + 1;
    }
    string Name;
    string Sport;
    short unsigned int Year;
    unsigned int Watchers;
    short unsigned int NumArena;
    friend ostream& operator<<(ostream& s, Stadium& el)
    {
        s << el.Name << '\t' << el.Sport << '\t' << el.Year << '\t' << el.Watchers << '\t' << el.NumArena << endl;
        return s;
    }
};

template <class T>
class Element
{
protected:
    Element* next;
    Element* prev;
    T info;

public:
    Element(T data)
    {
        next = prev = nullptr;
        info = data;
    }
    Element(Element* Next, Element* Prev, T data)
    {
        next = Next;
        prev = Prev;
        info = data;
    }
    Element(const Element& el)
    {
        next = el.next;
        prev = el.prev;
        info = el.info;
    }
    Element* getNext()
    {
        return next;
    }
    void setNext(Element* n)
    {
        next = n;
    }
    Element* getPrev()
    {
        return prev;
    }
    void setPrev(Element* p)
    {
        prev = p;
    }
    friend ostream& operator<<(ostream& s, Element<T>& el)
    {
        s << el.info;
        return s;
    }
    T getInfo()
    {
        return info;
    }
};

template <class T>
class LinkedList
{
protected:
    Element<T>* head;
    Element<T>* tail;
    int count;

public:
    LinkedList()
    {
        head = tail = nullptr;
        count = 0;
    }
    virtual Element<T>* pop() = 0;
    virtual Element<T>* push(T value) = 0;
    Element<T>& operator[](int index)
    {
        Element<T>* current = head;
        for (int i = 0;
            current != nullptr && i < index;
            current = current->getNext(), i++)
            ;
        return *current;
    }
    virtual bool isEmpty()
    {
        return (LinkedList<T>::count == 0);
    }
    friend ostream& operator<<(ostream& s, LinkedList<T>& el)
    {
        Element<T>* current;
        for (current = el.head; current != nullptr; current = current->getNext())
            s << *current;
        return s;
    }
    virtual ~LinkedList()
    {
        cout << "\nBase class destructor";
        //дописать деструктор базового класса
        head = nullptr;
        tail = nullptr;
    }
};

template <class T>
class FIFO : public LinkedList<T>
{
public:
    FIFO<T>() : LinkedList<T>() {}
    FIFO<T>(T* arr, int len) : LinkedList<T>(arr, len) {}
    Element<T>* push(T value)
    {
        if (LinkedList<T>::head == nullptr) //if(count==0)
        {
            //пустой список
            LinkedList<T>::head = new Element<T>(value);
            LinkedList<T>::tail = LinkedList<T>::head;
        }
        else
        {
            //элементы уже есть
            LinkedList<T>::tail->setNext(new Element<T>(value));
            (LinkedList<T>::tail->getNext())->setPrev(LinkedList<T>::tail) ;
            LinkedList<T>::tail = LinkedList<T>::tail->getNext();
        }
        LinkedList<T>::count++;
        return LinkedList<T>::tail;
    }
    void insert(T value, int index)
    {
        assert(!(index >= LinkedList<T>::count));
        int counter=0;
        Element<T>* current = LinkedList<T>::head;
        while (current != nullptr)
        {
            if (counter == index) { break; }
            current = current->getNext();
            counter++;
        }
        if (LinkedList<T>::head == nullptr)
        {
            //пустой список
            LinkedList<T>::head = new Element<T>(value);
            LinkedList<T>::tail = LinkedList<T>::head;
        }
        else if (LinkedList<T>::count == 1)
        {
            Element<T>* tmp = new Element<T>(value);
            LinkedList<T>::head = tmp;
            tmp->setNext(LinkedList<T>::tail);
            LinkedList<T>::tail->setNext(nullptr);
        }
        else if (index == 0)
        {
            Element<T>* tmp = new Element<T>(value);
            Element<T>* temp = LinkedList<T>::head;
            LinkedList<T>::head = tmp;
            temp->setPrev(tmp);
            tmp->setNext(temp);
        }
        else if (index == LinkedList<T>::count - 1)
        {
            Element<T>* tmp = new Element<T>(value);
            Element<T>* temp = LinkedList<T>::tail->getPrev();
            tmp->setNext(LinkedList<T>::tail);
            tmp->setPrev(temp);
            temp->setNext(tmp);
        }
        else
        {
            Element<T>* tmp = new Element<T>(value);
            tmp->setPrev(current);
            tmp->setNext(current->getNext());
            current->setNext(tmp);
            current = current->getNext();
            current->setPrev(tmp);

        }
        LinkedList<T>::count++;
        return;
    }
    void Remove(int index)
    {
        assert(!(index >= LinkedList<T>::count));
        assert(!(LinkedList<T>::count == 0));
        if (LinkedList<T>::count == 1)
        {
            LinkedList<T>::tail = LinkedList<T>::head = nullptr;
            LinkedList<T>::count = 0;
            return;
        }
        int counter = 0;
        Element<T>* current = LinkedList<T>::head;
        while (current != nullptr)
        {
            if (counter == index) { break; }
            current = current->getNext();
            counter++;
        }
        if (index == 0)
        {
            LinkedList<T>::head = LinkedList<T>::head->getNext();
            LinkedList<T>::head->setPrev(nullptr);
        }
        else if (index == LinkedList<T>::count - 1)
        {
            Element<T>* temp = LinkedList<T>::tail->getPrev();
            LinkedList<T>::tail = temp;
            temp->setNext(nullptr);
        }
        else
        {
            Element<T>* tmp = current->getPrev();
            current = current->getNext();
            tmp->setNext(current);
            current->setPrev(tmp);
        }
        LinkedList<T>::count--;

    }

    Element<T>* pop()
    {
        if (LinkedList<T>::head == nullptr)
            return nullptr;
        Element<T>* res = LinkedList<T>::head;
        if (LinkedList<T>::head == LinkedList<T>::tail)
            LinkedList<T>::head = LinkedList<T>::tail = nullptr;
        else
            LinkedList<T>::head = LinkedList<T>::head->getNext();
        LinkedList<T>::count--;
        return res;
    }
    ~FIFO()
    {
        cout << "destr fifo" << endl;
        while (LinkedList<T>::head != nullptr)
            pop();
    }
};

int main()
{
    srand(time(nullptr));
    FIFO<Stadium> a;
    Stadium arena;
    Stadium arena2;
    Stadium arena3;
    a.push(arena);
    a.push(arena2);

    cout << a;
    cout << endl;
    cout << a[0];
    cout << endl
        << endl;
    a.insert(arena3, 1);
    a.insert(arena3, 1);
    a.Remove(1);



    cout << a << endl;

    return 0;
}