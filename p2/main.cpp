//Удалить все нечетные числа в массиве . Вариант 7. Долгинцев Степан .КТСО-03-20

#include <iostream>
#include <stdlib.h>
#include <cassert>
using namespace std;

class MyArrayParent
{
protected:
	int capacity;

	int count;

	int* ptr;

public:
	MyArrayParent(int Dimension = 100)
	{
		ptr = new int[Dimension];
		capacity = Dimension;
		count = 0;
	}
	MyArrayParent(int* arr, int len)
	{
		assert(arr != nullptr);

		this->ptr = new int[len];
		this->count = len;
		this->capacity = 100;
		for (int i = 0; i < len; i++)
		{
			this->ptr[i] = arr[i];
		}
	}

	virtual ~MyArrayParent()
	{
		if (ptr != nullptr)
		{
			delete[] ptr;
			ptr = nullptr;
			capacity = 0;
			count = 0;
		}
	}

	int Capacity()
	{
		return capacity;
	}
	int Size()
	{
		return count;
	}
	int GetComponent(int index)
	{
		assert(!(index < 0) || !(index >= capacity));
		if (index >= 0 && index < count)
			return ptr[index];
	}
	void SetComponent(int value, int index)
	{
		assert(!(index < 0) || !(index >= capacity));
		if (index >= 0 && index < count)
			ptr[index] = value;
	}

	virtual void push(int value)
	{
		assert(!(count == capacity));
		if (ptr != nullptr)
		{
			count++;
			ptr[count - 1] = value;
		}
	}

	void RemoveLastValue()
	{
		count--;
	}

	int& operator[](int index)
	{
		assert(!(index < 0) || !(index >= capacity));
		return ptr[index];
	}

	MyArrayParent& operator=(const MyArrayParent& a)
	{
		if (this != &a)
		{
			if (a.ptr != nullptr)
			{
				delete[] ptr;
				ptr = nullptr;
			}
			this->ptr = new int[a.count];
			this->count = a.count;
			this->capacity = a.capacity;
			for (int i = 0; i < a.count; i++)
			{
				this->ptr[i] = a.ptr[i];
			}
		}
		return *this;
	}

	MyArrayParent(const MyArrayParent& a)
	{
		if (this != &a)
		{
			assert(a.ptr != nullptr);
			this->count = a.count;
			this->capacity = a.capacity;
			this->ptr = new int[count];
			for (int i = 0; i < count; i++)
			{
				this->ptr[i] = a.ptr[i];
			}
		}
	}

	virtual void print()
	{
		cout << "\nMyArrParent, size: " << count << ", values: {";

		for (int i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}" << endl;
		;
	}
};

class MyArrayChild : public MyArrayParent
{

public:

	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) {}
	MyArrayChild(int* arr, int len) : MyArrayParent(arr, len) {}
	MyArrayChild(const MyArrayChild& a) : MyArrayParent(a) {}

	virtual void print()
	{
		cout << "\nMyArrChild, size: " << count << ", values: {";

		for (int i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}" << endl;
		;
	}
	void RemoveAt(int index)
	{
		bool flag = false;
		assert(!((index < 0) || !(index >= capacity)));
		for (int i = 0; i < count; i++)
		{
			if ((i == index) && (flag == false))
			{
				flag = true;
			}
			else if (flag == true)
			{
				ptr[i - 1] = ptr[i];
			}
		}
		count--;

	}
	int IndexOf(int value)
	{
		for (int i = 0; i < count; i++)
		{
			if (ptr[i] == value)
			{
				return i;
			}
		}
		return -1;
	}

	virtual void InsertAt(int value, int index) final
	{
		assert(ptr != nullptr);
		assert(!(index < 0) || !(index >= capacity));
		count++;
		int tmp = 0;
		assert(!(count > capacity));
		//ptr[count] = 0;
		for (int i = 0; i < count; i++)
		{
			if (i == index)
			{
				tmp = ptr[i];
				ptr[i] = value;
			}
			else if (i > index)
			{
				swap(tmp, ptr[i]);
			}
		}


	}
	/*MyArrayChild Odd()
	{
		assert(ptr != nullptr);
		int oddn = 0;
		for (int i = 0; i < count; i++)
		{
			if (ptr[i] % 2 != 0) oddn++;
		}
		int* tmp = new int[count - oddn];
		int k = 0;
		for (int i = 0; i < count; i++)
		{
			if (ptr[i] % 2 == 1)
			{
				continue;
			}
			tmp[k] = ptr[i];
			k++;
		}
		MyArrayChild a(tmp, count - oddn);
		MyArrayChild b = a;
		return b;
	}*/

};
int comp(const void* a, const void* b) //функция для сортировки по возрастанию (компаратор)
{
	return (*(int*)a - *(int*)b);
}
class MySortedArray : public MyArrayChild
{
public:
	MySortedArray(int Dimension = 100) : MyArrayChild(Dimension) {}
	MySortedArray(int* arr, int len)
	{
		this->ptr = new int[len];
		this->count = len;
		capacity = 100;
		for (int i = 0; i < len; i++)
		{
			this->ptr[i] = arr[i];
		}
		qsort(ptr, count, sizeof(int), comp);
	}
	MySortedArray(const MySortedArray& a)
	{
		assert(a.ptr != nullptr);
		this->count = a.count;
		this->capacity = a.capacity;
		this->ptr = new int[count];
		for (int i = 0; i < count; i++)
		{
			this->ptr[i] = a.ptr[i];
		}
	}
	MySortedArray& operator=(const MySortedArray& a)
	{
		assert(a.ptr != nullptr);
		this->count = a.count;
		this->capacity = a.capacity;
		for (int i = 0; i < count; i++)
		{
			this->ptr[i] = a.ptr[i];
		}
		return *this;
	}
	virtual void push(int value) override
	{
		assert(!(ptr == nullptr));

		bool flag = true;

		count++;
		assert(!(count > capacity));
		ptr[count - 1] = value;
		while (flag)
		{
			flag = false;
			for (int i = 0; i < count - 1; i++)
			{
				if (ptr[i] > ptr[i + 1])
				{
					swap(ptr[i], ptr[i + 1]);
					flag = true;
				}
			}
		}

	}
	virtual void print() override
	{
		cout << "\nMySortedArray, size: " << count << ", values: {";

		for (int i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}" << endl;
		;
	}
	MySortedArray Odd()
	{
		assert(ptr != nullptr);
		int oddn = 0;
		for (int i = 0; i < count; i++)
		{
			if (this->ptr[i] % 2 != 0) { oddn++; }
		}
		int* tmp = new int[count - oddn];
		int k = 0;
		for (int i = 0; i < count; i++)
		{
			if (this->ptr[i] % 2 == 1)
			{
				continue;
			}
			tmp[k] = ptr[i];
			k++;
		}

		return MySortedArray(tmp, count - oddn);

	}


};

int main()
{
	int ptr1[4] = { 2, 3, 1, 4 };
	MySortedArray arr(ptr1, 4);
	arr.push(0);
	MySortedArray aq;
	aq = arr.Odd();
	aq.print();
	//arr.SetComponent(3,3);
	//arr.InsertAt(55,2);
	//arr.Odd();
	arr.print();
	return 0;
}