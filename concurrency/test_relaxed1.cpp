#include<iostream>
#include<atomic>
#include<thread>


using namespace std;
const int cnt = 10;
atomic<bool> flag(false);
atomic<int> x(0), y(0), z(0);

struct Node{
    int x;
    int y;
    int z;
};
Node values1[cnt] ;
Node values2[cnt] ;
Node values3[cnt] ;
Node values4[cnt] ;
Node values5[cnt] ;

void write_value(atomic<int> * value_to_write, Node *values) {

    while(!flag) {
        this_thread::yield();
    }

    for (size_t i = 0; i < cnt; i++)
    {
        /* code */

        values[i].x = x.load(memory_order_relaxed);
        values[i].y = y.load(memory_order_relaxed);
        values[i].z = z.load(memory_order_relaxed);
        value_to_write->store(i+1, memory_order_relaxed);
        this_thread::yield();
    }
}

void read_values(Node *values)
{
    while (!flag)
    {
        this_thread::yield();
    }

    for (size_t i = 0; i < cnt; i++)
    {
        /* code */

        values[i].x = x.load(memory_order_relaxed);
        values[i].y = y.load(memory_order_relaxed);
        values[i].z = z.load(memory_order_relaxed);
        this_thread::yield();
    }
}

void print_values(Node *values)
{
  

    for (size_t i = 0; i < cnt; i++)
    {
        /* code */
        if (i)
        {
            cout << ",";
        }

        cout << "(" << values[i].x<< "," << values[i].y << "," << values[i].z << ")" ;
    }
    cout <<endl;
}

int main(int argc, char ** argv) {

    thread t1(write_value, &x, values1);
    thread t2(write_value, &y, values2);
    thread t3(write_value, &z, values3);
    thread t4(read_values,  values4);
    thread t5(read_values,  values5);
    flag = true;
    t5.join();
    t4.join();
    t1.join();
    t2.join();
    t3.join();
    print_values(values1);
    print_values(values2);
    print_values(values3);
    print_values(values4);
    print_values(values5);
    return 0;

}
