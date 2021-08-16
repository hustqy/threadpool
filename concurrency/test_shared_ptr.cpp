
#include <iostream>
#include <memory>

using namespace std;

class Test : public enable_shared_from_this<Test>
{

public:
    Test() { cout << "Test" << endl; }
    Test(int a) : a(a) { cout << "Test iinit" << endl; }

    shared_ptr<Test> sp_get()
    {
        return shared_from_this();
    }

    ~Test() { cout << "~Test" <<endl;}

    int getA() { return a; }
    int setA(int a) { this->a = a;}

private:
    int a;
};

void fix_Test(shared_ptr<Test> tt) { 

    tt->setA(199);
    cout << "use count" <<  tt.use_count() << endl;
}


int main(int argc, char ** argv) {

    shared_ptr<Test> sp (new Test(10));
    //Test * sp = new Test(10);
    shared_ptr<Test> sp1 ( sp->sp_get());
    cout << sp1.use_count() << endl;
    cout  << sp1-> getA() << endl;
   // cout<< sp.use_count() << endl;
    return 0;


}