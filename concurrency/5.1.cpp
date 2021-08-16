#include<iostream>

using namespace std;

struct Test {

    int a ;
    int f1:1;
    int f2:2;
    int f4:4;
    int f5:16;

    int :0;
    int f6;

};

int main(int argc, char **argv)
{

    Test test;
    test.a = -1;
    test.f1 = 1;
    test.f2 = 0x3;
    test.f4 = 0xf;
    test.f5 = 0x2222;
    int f6  = 0x12345678;

    cout<< "f1" << test.f1 <<endl;
    return 0;
}