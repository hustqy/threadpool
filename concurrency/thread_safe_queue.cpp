#include<iostream>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<thread>
#include<functional>

template<class T> class my_queue{


    private:
      std::queue<T> m_queue;

      std::mutex m_mutex;
      std::condition_variable cv;

    public:
        my_queue() {
            
        }
        void push_queue(T it) {

            std::cout << "push threadid " <<std::this_thread::get_id() << std::endl;
            {
            std::lock_guard<std::mutex> lock(m_mutex);
             m_queue.push(it);
            }
            cv.notify_one();

        }

        
        void consume_queue() {

            std::cout << "consume threadid " <<std::this_thread::get_id() << std::endl;
            std::unique_lock<std::mutex> lock(m_mutex);

            cv.wait(lock, [this] (){return !m_queue.empty();});

            // consume queue
            while(!m_queue.empty())
            {
                /* code */
                T it = m_queue.front();
                m_queue.pop();
                std::cout<< it<<std::endl;
            }

            lock.unlock();
                        
        }



};



int main(int argc, char ** argv ) {


    const int  &ref2 = 1;// OK.编译器产生临时变量，需要const引用

    my_queue<int> queue;
    //std::thread t(&my_queue<int>::consume_queue, std::ref(queue));
    std::thread t( [=,&queue]() { queue.consume_queue(); } );

    queue.push_queue(1);
    queue.push_queue(2);
    t.join();
    return 0;
}