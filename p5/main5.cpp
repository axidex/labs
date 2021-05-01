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


template<typename T>
class BaseMatrix
{
public:
    T** ptr;
    int height;
    int width;
public:
    BaseMatrix(int Height = 2, int Width = 2)
    {
        if (Height <= 0 || Width <= 0)
            throw WrongSizeException("Non-positive size of matrix");
        height = Height;
        width = Width;
        ptr = new T* [height];
        for (int i = 0; i < height; i++)
            ptr[i] = new T[width];
    }
    BaseMatrix<T>(const BaseMatrix& M)
    {
        height = M.height;
        width = M.width;
        ptr = new T* [height];
        for (int i = 0; i < height; i++)
        {
            ptr[i] = new T[width];
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
    int GetHeigth()
    {
        return this->height;
    }
    int GetWidth()
    {
        return this->width;
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
    T& operator()(int row, int column)
    {
        if (row < 0 || column < 0 || row >= height || column >= width)
            throw OutOf("Index is out of bounds");
        return ptr[row][column];
    }
    friend ostream& operator<<(ostream& ustream, const BaseMatrix<T>& obj)
    {
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
    friend istream& operator>>(istream& ustream, BaseMatrix<T>& obj)
    {
        if (typeid(ustream) == typeid(ifstream))
            ustream >> obj.height >> obj.width;
        for (int i = 0; i < obj.height; i++)
            for (int j = 0; j < obj.width; j++)
                ustream >> obj.ptr[i][j];
        return ustream;
    }
};

template <typename T>
class Matrix2 : public BaseMatrix<T>
{
public:
    Matrix2(int Height = 2, int Width = 2) :BaseMatrix<T>(Height = 2, Width = 2) {};
    Matrix2(const Matrix2& M) :BaseMatrix<T>(M) {};
    Matrix2(string filename,int Height,int Width)
    {
        if (Height <= 0 || Width <= 0)
            throw WrongSizeException("Non-positive size of matrix");
        this->height = Height;
        this->width = Width;
        this->ptr = new T * [this->height];
        for (int i = 0; i < this->height; i++)
            this->ptr[i] = new T[this->width];
        ifstream fin(filename);
        assert(fin.is_open());
        for (int i = 0; i < Height; i++)
        {
            for (int j = 0; j < Width; j++)
            {
                fin >> this->ptr[i][j];
            }
        }

         fin.close();
       
    }
    void const Save(string filename)
    {
        ofstream fout(filename);
        assert(fout.is_open());
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    fout << this->ptr[i][j] << '\t';
                }
                fout << endl;
            }
            fout.close();
        
    }
    void fill()
    {   
            srand(time(nullptr));
            for (int i = 0; i < this->height; i++)
            {
                for (int j = 0; j < this->width; j++)
                {
                    this->ptr[i][j] = rand() % 10;
                }
            }
    }
    vector<T> Sum()
    {
            int sum = 0;
            vector<T> vec;
            for (int i = 0; i < this->height; i++)
            {
                sum = 0;
                for (int j = 0; j < this->width; j++)
                {
                    sum += this->ptr[i][j];
                }
                vec.push_back(sum);
            }
            return vec;
    }
};
int main()
{
    /*try
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
   */
    Matrix2<int> M(2,2);
    cout << M(1, 1) << endl;
    M.fill();
    cout << M.GetHeigth()<< endl;
    cout << M(1,1) << endl;
    vector<int> vec(M.Sum());
    cout<<vec.size();
    for (auto element : vec)
    {
        cout << element << endl;
    }
    
    /*vector<int> vec = M.Sum();
    for (auto element : vec)
    {
        cout << element << endl;
    }
    cout << M;
    M.Save("out.txt");

    cout << endl;


    Matrix2<int> in("out.txt",2,2);
    
    in.print();
    */
    
    return 0;
}