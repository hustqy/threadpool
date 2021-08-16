#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<execution>
#include<ranges>

using namespace std;

int count_lines(const std::string& filename) {

    std::ifstream in(filename, std::ios::binary);
    return std::count(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), '\n');
}

vector<int> count_files(const std::vector<std::string> & files) {

    auto res = files | std::ranges::views::transform(count_lines);
    
     vector<int> a = vector<int>(res.begin(), res.end());
    return a;
    
}

double average_score(std::vector<int> & scores) {

    return std::reduce(std::execution::par, scores.begin(), scores.end(), 0) / (double)(scores.size());
}

int main() {

    std::string a[] = {"C:\\Users\\hushangxing\\Desktop\\1.txt", "C:\\Users\\hushangxing\\Desktop\\2.txt"};
    std::vector<std::string> cc(a, a+1);
    auto res = count_files(cc);
    for(auto i : res){
        cout<< i;
    }
    vector<int> ss = {1,2,3};
    double d = average_score(ss);
    cout <<d <<endl;

    string c = "1111";
    auto b = std::move(c);

    cout <<"c" <<c << "b" << b;


    return 0;
}