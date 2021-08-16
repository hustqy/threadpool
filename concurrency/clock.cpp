#include<iostream>
#include<chrono>
#include<thread>
#include<ratio>
#include<iomanip>
#include<ctime>
#include <iomanip>
#include <algorithm>


void slow_motion()
{
    static int a[] {1,2,3,4,5,6,7,8,9,10,11,12};
    while (std::next_permutation(std::begin(a), std::end(a))) { }
}

int main(int argc, char ** argv) {

    auto now= std::chrono::system_clock::now();
    auto oneMinAgo = std::chrono::system_clock::to_time_t(now - std::chrono::seconds(60));

//   std::time_t t = std::time(nullptr);
 //   std::cout << "UTC:       " << std::put_time(std::gmtime(&t), "%c %Z") << '\n';
  //  std::cout << "local:     " << std::put_time(std::localtime(&t), "%c %Z") << '\n';
    std::cout << "60s ago time is " << std::put_time(std::localtime(&oneMinAgo), "%c %Z") <<std::endl;



    auto start = std::chrono::steady_clock::now();
    slow_motion();

    auto end = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration_cast< std::chrono::microseconds> (end - start).count() << " us" << std::endl;

    std::chrono::duration<double, std::ratio<60,1> > duration;
    return 0;


}