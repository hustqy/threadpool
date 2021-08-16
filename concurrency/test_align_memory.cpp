#include <iostream>
#include <utility>
#include <new>
#include <type_traits>

using namespace std;

template <typename T, size_t N>
class align_vector
{

public:
    template<typename ...Args>
    void emplace_back(Args&&... args)
    {

       if(size >= N)  {
           throw bad_alloc();
       }
        new (data + size++) T(forward<Args>(args)...);
    }

    const T& operator[](size_t i)
    {
        return *reinterpret_cast<T*>(data + i);
    }
    

    ~align_vector() {
        for (size_t i = 0; i < size; i++)
        {
            /* code */
            reinterpret_cast<T*>(data + i) -> ~T();
        }
        
    }

private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data[N];
    int size = 0;
};


int main(int argc, char ** argv ) {

     align_vector<string, 10> vector;
     for (size_t i = 1; i <= 10; i++)
     {
         /* code */
     vector.emplace_back(i, '*');
     }
     cout << vector[8] << endl;

     return 0;

}