#include<iostream>

#include<condition_variable>
#include<thread>
#include<mutex>

using namespace std;

mutex mt;
condition_variable cv;
int k = 0;
void func() { 

    unique_lock<mutex> lock(mt);
    cv.wait(lock, []() {return k==1; });    
    cout << "after " << k << endl;

}

int main(int argc, char **argv) {

    thread t1(func);
    {
        unique_lock<mutex> lock(mt);
        k = 1;
        cv.notify_all();
    }

    t1.join();
    return 0;

}