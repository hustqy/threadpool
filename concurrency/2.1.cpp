#include <iostream>
#include <thread>


class Backgroud_task {

    public:
        void operator()() const { 

            func1();
            func2();
    
        }

        void func1() const {

            std::cout << "func1" << std::endl;
        }
        
        void func2() const {
            std::cout << "func2" << std::endl;
        }
};

int main(int argc, char **argv) { 



    //std::thread mythread((Backgroud_task()));
    std::thread mythread(Backgroud_task());
    
    return 0;
}