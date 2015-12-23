#include <iostream>
using namespace std;
class a{
public:
	void fun1(){
		fun2();
	}
	virtual void fun2(){
		cout << "a::fun2" << endl;
	}
};
class b:public a{
public:
	virtual void fun2(){
		cout << "b::fun2" << endl;
	}
};
int main(){
	b B;
	a *pa = &B;
	pa->fun1();
	system("pause");
	return 0;
}