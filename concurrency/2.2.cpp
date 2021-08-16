#include<iostream>
#include<thread>

class MyClass {

    private :
        int a ;

    public:
        MyClass(int a ){ this->a = a; std::cout << "MyClass" << std::endl;};

        ~MyClass(){ std::cout << " ~ MyClass" << std::endl;};
        MyClass(const MyClass& other) { this-> a = other.a ; std::cout << "copy" << std::endl;};

        int getA() {return a;}

};

void f ( MyClass& obj) {

    std::cout << "function f" << obj.getA() << std::endl;
}

int main (int argc, char ** argv) {

    char buf[100];
    int i = 10;
    sprintf(buf, "hellow word %d", i);
    std::string str2 = "hello2";

    MyClass b(11);

    std::thread t(f,std::ref(b));
    t.detach();
    std::cout << "main end" << std::endl;

    return 0;

}