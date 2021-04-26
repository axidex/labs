/*
Получить вектор, каждая компонента которого содержит
сумму элементов из соответствующей строки матрицы.
Вариант-7 
Долгинцев КТСО-03-20
*/

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <cstring>
#include <vector>
#include <cassert>


using namespace std;

class Exception : public std::exception
{
protected:
    //сообщение об ошибке
    char* str;

public:
    Exception(const char* s)
    {
        str = new char[strlen(s) + 1];
        strcpy_s(str, strlen(s) + 1, s);
    }
    Exception(const Exception& e)
    {
        str = new char[strlen(e.str) + 1];
        strcpy_s(str, strlen(e.str) + 1, e.str);
    }
    ~Exception()
    {
        delete[] str;
    }
    //функцию вывода можно будет переопределить в производных
    //классах, когда будет ясна конкретика
    virtual void print()
    {
        cout << "Exception: " << str;
    }
};
class OutOf : public Exception
{
public:
    OutOf(const char* s) : Exception(s) {}
    OutOf(const OutOf& e) : Exception(e) {}
    virtual void print() override
    {
        cout << "IndexOutOfBounds: " << str;
    }
};
class WrongDimensionsException : public Exception
{
public:
    WrongDimensionsException(const char* s) : Exception(s) {}
    WrongDimensionsException(const WrongDimensionsException& e) : Exception(e) {}
    virtual void print() override
    {
        cout << "WrongDimensionsException: " << str;
    }
};
class WrongSizeException : public WrongDimensionsException
{
public:
    WrongSizeException(const char* s) : WrongDimensionsException(s) {}
    WrongSizeException(const WrongSizeException& e) : WrongDimensionsException(e) {}
    virtual void print() override
    {
        cout << "WrongSizeException: " << str;
    }
};

class BaseMatrix
{
protected:
    double** ptr;
    int height;
    int width;

public:
    BaseMatrix(int Height = 2, int Width = 2)
    {
        if (Height <= 0 || Width <= 0)
            throw WrongSizeException("Non-positive size of matrix");
        height = Height;
        width = Width;
        ptr = new double* [height];
        for (int i = 0; i < height; i++)
            ptr[i] = new double[width];
    }
    BaseMatrix(const BaseMatrix& M)
    {
        height = M.height;
        width = M.width;
        ptr = new double* [height];
        for (int i = 0; i < height; i++)
        {
            ptr[i] = new double[width];
            for (int j = 0; j < width; j++)
                ptr[i][j] = M.ptr[i][j];
        }
    }
    ~BaseMatrix()
    {
        if (ptr != nullptr)
        {
            for (int i = 0; i < height; i++)
                delete[] ptr[i];
            delete[] ptr;
            ptr = nullptr;
        }
    }
    void const print()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
                cout << ptr[i][j] << " ";
            cout << "\n";
        }
    }
    double& operator()(int row, int column)
    {
        if (row < 0 || column < 0 || row >= height || column >= width)
            throw OutOf("Index is out of bounds");
        return ptr[row][column];
    }
    friend ostream& operator<<(ostream& ustream, BaseMatrix
        obj);
    friend istream& operator>>(istream& ustream, BaseMatrix&
        obj);
};
ostream& operator<<(ostream& ustream, BaseMatrix obj)
{
    //ustream<<my_manip;
    if (typeid(ustream).name() == typeid(ofstream).name())
    {
        ustream << obj.height << " " << obj.width << "\n";
        for (int i = 0; i < obj.height; i++)
        {
            for (int j = 0; j < obj.width; j++)
                ustream << obj.ptr[i][j] << "\n";
        }
        return ustream;
    }
    for (int i = 0; i < obj.height; i++)
    {
        for (int j = 0; j < obj.width; j++)
            ustream << obj.ptr[i][j] << " ";
        ustream << "\n";
    }
    return ustream;
}
istream& operator>>(istream& ustream, BaseMatrix& obj)
{
    if (typeid(ustream) == typeid(ifstream))
        ustream >> obj.height >> obj.width;
    for (int i = 0; i < obj.height; i++)
        for (int j = 0; j < obj.width; j++)
            ustream >> obj.ptr[i][j];
    return ustream;
}
ostream& my_manip(ostream& s)
{
    s.precision(4);
    s.fill('%');
    s.width(10);
    return s;
}
class Matrix2 : public BaseMatrix
{
public:
    Matrix2(int Height = 2, int Width = 2) : BaseMatrix(Height=2,Width=2){}
    Matrix2(const BaseMatrix& M) : BaseMatrix(M) {}
    Matrix2(string filename)
    {
        ifstream fin(filename);
        assert(fin.is_open());
        
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                fin >> ptr[i][j];
            }
        }

         fin.close();
       
    }
    void const Save(string filename)
    {
        ofstream fout(filename);
        assert(fout.is_open());
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    fout << ptr[i][j] << '\t';
                }
                fout << endl;
            }
            fout.close();
        
    }
    void fill()
    {
        srand(time(nullptr));
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                ptr[i][j] = rand() % 10;
            }
        }
    }
    vector<int> Sum()
    {
        int sum = 0;
        vector<int> vec;
        for (int i = 0; i < height; i++)
        {
            sum = 0;
            for (int j = 0; j < width; j++)
            {
                sum += ptr[i][j];
            }
            vec.push_back(sum);
        }
        return vec;
    }
};
int main()
{
    try
    {
        //BaseMatrix Wrong(0, 2);
        //Wrong(10, 10);
    }
    catch (OutOf e)
    {
        cout << "\nException has been caught: ";
        e.print();
    }
    catch (WrongSizeException e)
    {
        cout << "\nException has been caught: ";
        e.print();
    }
    cout << "\n";
    Matrix2 M;
    M.fill();
    vector<int> vec = M.Sum();
    for (auto element : vec)
    {
        cout << element << endl;
    }
    cout << M;
    M.Save("out.txt");

    cout << endl;


    Matrix2 in("out.txt");
    
    in.print();
    
    
    return 0;
}