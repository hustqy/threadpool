#include<iostream>
#include<atomic>
#include<thread>
#include<cassert>

using namespace std;
atomic<bool> x(0), y(0);

void write_x_then_y() {

    x.store(true, memory_order_relaxed);
    atomic_thread_fence(memory_order_release);
    y.store(true, memory_order_relaxed);
}

void read_y_then_x()
{
    while(!y.load(memory_order_relaxed));
    atomic_thread_fence(memory_order_acquire);

    assert(x.load(memory_order_relaxed));
}

int main(int argc, char ** argv) {

    thread t1(write_x_then_y);
    thread t2(read_y_then_x);
    t2.join();
    t1.join();
    return 0;

}
