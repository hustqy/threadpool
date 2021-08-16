
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class person
{

    bool is_femail;
    int age;

public:

    person(){};
    person(int age) : is_femail(false), age(age)
    {
    }
    person(int age, bool is_femail) : is_femail(is_femail), age(age)
    {
    }

    bool getIsFemail() { return is_femail; };

    int getAge() { return age; };
};

bool is_female(person p)
{
    return p.getIsFemail();
}

int main()
{

    std::vector<person> source;
    source.emplace_back(10);
    source.emplace_back(11, true);
    source.emplace_back(12 , true);

    std::vector<person> dst;

    copy_if(source.begin(), source.end(),std::back_inserter(dst), is_female);
    for(auto p : dst) {
        cout  << p.getAge()<< std::endl;
    }
    return 0;
}