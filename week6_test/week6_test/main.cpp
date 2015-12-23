#include <iostream>
using namespace std;
class A{
public:
	virtual void print(){
		cout << "A::print" << endl;
	}
	
};
class B :public A{
public:
	virtual void print(){
		cout << "B::print" << endl;
	}
};
class C :public A{
	virtual void print(){
		cout << "C::print" << endl;
	}
};
class D :public A{
	virtual void print(){
		cout << "D::print" << endl;
	}
};
int main()
{
	A a;
	B b;
	C c;
	D d;
	A *pa = &a;
	B *pb = &b;
	C *pc = &c;
	D *pd = &d;
	pa->print(); 
	pa = pb;
	pa->print();
	pa = pc;
	pa->print();
	pa = pd;
	pa->print();

	system("pause");
	return 0;
}