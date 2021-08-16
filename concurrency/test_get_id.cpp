

#include <iostream>
#include <thread>
using namespace std;
void show(int n){
		cout<<"show1:get_id() is "<<this_thread::get_id()<<",Now n is "<<n<<endl;
}
void show2(int n){
	
		cout<<"show2:get_id() is "<<this_thread::get_id()<<",Now n is "<<n<<endl;
}
int main()
{
	cout<<"main starts"<<endl;
	cout<<"mainThread is "<<this_thread::get_id()<<endl;
	thread t2(show,10);
	cout<<"t2 is "<<t2.get_id()<<endl;
	t2.join();
	cout<<"after t2.join(),t2 is "<<t2.get_id()<<endl;
	
	thread t3(show2,99);
	cout<<"t3 is "<<t3.get_id()<<endl;
	t3.detach();
	cout<<"after t3.detach(),t3 is "<<t3.get_id()<<endl;
	
	cout<<"main complete!"<<endl;

    return 0;
}