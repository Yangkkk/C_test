#include <iostream>
using namespace std;

class myclass {
public:
	virtual void hello(){ cout << "hello from myclass" << endl; };
	virtual void bye(){ cout << "bye from myclass" << endl; }
};
class son :public myclass{
public:
	void hello(){ cout << "hello from son" << endl; };
	son(){ hello(); };
	~son(){ bye(); };
};
class grandson :public son{
public:
	void hello(){ cout << "hello from grandson" << endl; };
	void bye() { cout << "bye from grandson" << endl; }
	grandson(){ cout << "constructing grandson" << endl; };
	~grandson(){ cout << "destructing grandson" << endl; };
};
int main(){
	grandson gson;
	son *pson;
	pson = &gson;
	pson->hello(); //∂‡Ã¨
	return 0;
}
