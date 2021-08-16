
#include<iostream>

using namespace std;

class A
{
public:
    virtual void Funtest1()
    {
        cout << "A::Funtest1" << endl;
    }
};

class B1:public virtual A
{
public:
    virtual void Funtest2()
    {
        cout << "B1::Funtest2" << endl;
    }
};

class B2 :public virtual A
{
public:
  virtual void Funtest2()
    {
        cout << "B2::Funtest2" << endl;
    }

    virtual void Funtest3()
    {
        cout << "B2::Funtest3" << endl;
    }

};

class C :public virtual B1,public virtual B2
{
public:
    // virtual void Funtest2()
    // {
    //     cout << "C::Funtest2" << endl;
    // }

    virtual void Funtest4()
    {
        cout << "C::Funtest4" << endl;
    }
};


typedef void(*PVTF)();//函数指针

void PrintVpt()//打印虚表
{
    A a;
    B1 b1;
    B2 b2;
    C c;
    PVTF* pVtf = (PVTF*)(*(int*)&c);

    while (*pVtf)
    {
        (*pVtf)();
        pVtf++;
    } 
    B2 &b = c;
     pVtf = (PVTF*)*(int*)&b;
    while (*pVtf)
    {
        (*pVtf)();
        pVtf++;
    }
}
void test()
{

    cout << sizeof(B1) << endl;
    cout << sizeof(B2) << endl;
    cout << sizeof(C) << endl;
    PrintVpt();
}

int main (int argc, char ** argv) {

    /* C * b1 = new C();
    b1->B1::Funtest2(); */
    test();
    return 0;
}