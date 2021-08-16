#include<iostream>
#include<thread>
#include<functional>
#include<future>

std::future<int> my_task(std::function<int(int)> func, int i) {

    std::packaged_task<int(int)> task{func};

    std::future<int> fu= task.get_future();

    std::thread t{std::move(task),i };
    t.detach();
    return fu;
}


void get_val(std::promise<int> & promise) {

    try {

        std::cout << "get val thread " <<std::this_thread::get_id() << std::endl;
        std::future<int> f = promise.get_future();
        int r = f.get();
        std::cout << r << std::endl;
    } catch (std::exception e) {
        std::cout << e.what() << std::this_thread::get_id() << std::endl;
    }
}

void set_val(std::promise<int> & promise) {

    std::cout << "set val thread"<<std::this_thread::get_id() << std::endl;
    promise.set_value(111);

}

int func(int i) {
    return i * i;
}
int main(int argc, char ** argv) {

    //std::future<int> t = my_task(func, 10);
    //std::cout << t.get() << std::endl;
    
    std::promise<int> promise;
    std::thread t1(set_val, std::ref(promise));
    std::thread t3(get_val, std::ref(promise));
    std::thread t2(get_val, std::ref(promise));
    return 0;
}