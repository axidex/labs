#include<iostream>
#include<cmath>
#include<cassert>

using namespace std;
//Вариант 7 
//1.1
//Унарный плюс – применение модуля к
//действительной и мнимой части, бинарный
//оператор / - стандартное деление на действительное
//и комплексное число
//1.2
//Бинарный оператор / - стандартное деление
//действительного числа на комплексное число


class IM
{
    protected:

    double re;
    double im;
    
    public:

    IM() {re = 0; im = 0;}
    IM(double re) {this->re = re;}
    IM(double re, double im) {this->re = re;this->im = im;}
    
    IM(const IM& F) {re = F.re; im= F.im;}

    IM operator +()
    {
        IM Res;
        Res.re = abs(re);
        Res.im = abs(im);

        return Res;
        /*
        re = abs(re);
        im = abs(im);
        return *this;*/
        //return IM(abs(this->re), abs(this->im));
    }
    IM operator /(const IM& F)
    {
        assert(F.im*F.im+F.re*F.re!=0);
        IM Res;
        Res.re = (F.re*this->re+ F.im*this->im)/(F.im*F.im+F.re*F.re);
        Res.im = (F.re*this->im-this->re*F.im)/(F.im*F.im+F.re*F.re);
        return Res;
        
    }

    IM operator /(double F)
    {
        assert (F != 0);
        
        IM Res;
        Res.re = this->re/F;
        Res.im = this->im/F;
        return Res;
        
    }
    
    void print() const
    {
      cout<<re<<'+'<<'('<<im<<'i'<<')'<<endl;
    }
    
    
};

class IM2 : public IM
{
   
    
    public: 
    IM2():IM() {}
    IM2(double re):IM(re) {}
    IM2(double re, double im):IM(re,  im) {}   
    IM2(const IM& F):IM(F) {}
    friend IM2 operator /(const double N,const IM2& F);

};
IM2 operator /(double N,const IM2& F)
    {    
        assert(F.re*F.re + F.im*F.im!=0);
        double imnum;
        double renum;
        double div;
        div = F.re*F.re + F.im*F.im;
        imnum = (-N*F.im)/div;
        renum = (N*F.re)/div;
        
        return IM2 (renum,imnum); 
    }


int main()
{
       
    IM F1(-2, -3);
    IM2 F2(1, 3);
    IM2 F0(-12,-10);
    double q = 3;
    F1=+F1;
    //+F0;
    F1.print();
    
    
    


    return 0;
}