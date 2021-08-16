#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
#include<forward_list>
#include<iterator>

template<typename ForwardIt>
void quickSort(ForwardIt begin, ForwardIt end) {

    if (begin == end) {
        return;
    } ;
    ForwardIt
            pivot = std::next(begin, std::distance(begin, end) / 2);

    typedef typename std::iterator_traits<ForwardIt>::value_type value_type;
        ForwardIt middle1 = std::partition(begin, end, [&](value_type em) { return em < *pivot; });
    ForwardIt middle2 = std::partition(middle1, end, [&](value_type em) {return em <= *pivot;});
    quickSort(begin, middle1);
    quickSort(middle2, end);

}

int main() {


    std::list<int> a{123,32,54,12,45};
    quickSort(a.begin(), a.end());

    for(auto i : a) {
        std::cout << i << std::endl;
    }
    return 0;

}