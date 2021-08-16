#include<iostream>
#include<atomic>
#include<thread>

using namespace std;

atomic<int> flag(0);
atomic<int> data[4];

void thread1() {

    for (size_t i = 0; i < 4; i++)
    {
        /* code */
        data[i].store(i, memory_order_relaxed);
    }
    
    flag.store(1, memory_order_relaxed);
}

void thread2() {
    int expected = 2;
    while(!flag.compare_exchange_strong(expected, 2, memory_order_acq_rel));
}

void thread3() { 

    while( flag.load( memory_order_acquire ) < 2);
    cout << data[0] << endl;
}

int main(int argc, char ** argv) {
    thread t1(thread1);
    thread t2(thread2);
    thread t3(thread3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
