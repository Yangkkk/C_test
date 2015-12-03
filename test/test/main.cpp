#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
class A
{
private:
	int v;
public: 
	A(int i){
		cout << "1" << endl;
		v = i;
	}
	A(){ cout << "2" << endl; }
};
int main()
{
	A a1(4);
	A a2 = 5;
	A a3;
	a3 = 9;
	A a4, a5;
	a4 = a5;
	getchar();
	return 0;
}