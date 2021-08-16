
#include<future>
#include<thread>
#include<iostream>
#include<algorithm>
#include <functional>
#include <type_traits>
#include <vector>


/// 4.17



template<typename Func, typename... Args> 
auto spawn_task(Func && func, Args&&... args) -> std::future<decltype(func(args...))> { 

    using ret_type = decltype(func(args...));

    return std::async(func, args...);

}


template<typename Func, typename... Args> 
auto spawn_task2(Func && func, Args&&... args) -> std::future<decltype(func(args...))> { 


    using ret_type = decltype(func(args...));

    auto f =std::bind(func, args...);

    std::packaged_task<ret_type()> task(f);
    std::future<ret_type> future = task.get_future();

    task();
    // using  ret_type2 = decltype( std::declval<Func>()(args...)) ;
    // std::packaged_task<ret_type(Args...)> task(func);
    
    // std::future<ret_type> future = task.get_future();
    // std::thread t(std::move(task), std::forward<Args>(args)...);
    // t.join();

    return future ;
}


template<typename Func, typename... Args> 
auto spawn_sync(Func && func, Args&&... args) -> std::future<decltype(func(args...))> { 
    using ret_type = decltype(func(args...));
    std::promise<ret_type> p ;
    auto res = p.get_future();
    std::thread t(
        [&]() mutable {
                try {
                    p.set_value_at_thread_exit(func(args...));
                } catch (...) {
                    p.set_exception_at_thread_exit(std::current_exception());
                }
        }
    );
    t.join();
    return res;
}



int func(std::string str) { 

    std::sort(str.begin(), str.end());
    int cnt  = 0;
    do {
        //std::cout << str << std::endl;
        cnt ++;
         
    } while (std::next_permutation(str.begin(), str.end()));
    return cnt;
}

std::future<int> parallel() { 

    std::vector<std::future<int>> res;
    for (int i = 0; i < 10; i++) {
        res.push_back(spawn_sync(func, std::string("ad")));
    }

    return std::async([all = std::move(res)](){

        int sum = 0;
        for(auto &fu: all) {
            std::future<int> & t = const_cast<std::future<int> &>(fu);
            sum+= t.get();
        }
        return sum;

    });
}

int main(int argc, char ** argv) {

    /* std::future<int> a= spawn_sync(func, "dead");

    std::cout << a.get() << std::endl; */
    std::future<int> fu = parallel();
    std::cout << fu.get() << std::endl;

    return 0;
}