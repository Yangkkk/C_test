#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
class Csmaple{
private: 
	int n;
public:
	Csmaple(){
		cout << "sample1" << endl;
	}
	Csmaple(const Csmaple &c){
		v = c.v;
		cout << "copy construct" << endl;
	}
	int v;
	Csmaple(int x){
		v = x;
		cout << "sample2" << endl;
	}
	Csmaple(int x, int y){
		cout << "sample3" << endl;
	}
};
void func1(Csmaple s1){

}
Csmaple func2(){
	Csmaple d(4);
	return d;
}
int main()
{
	cout << "s1" << endl;
	Csmaple arry1[2];
	cout << "s2" << endl;
	Csmaple arry2[2] = { 1, 2 };
	cout << "s3" << endl;
	Csmaple arry3[2] = { 3 };
	cout << "s4" << endl;
	Csmaple *arry4 = new Csmaple[2];
	delete arry4;

	cout << "s5" << endl;
	Csmaple arry5[3] = { 1, Csmaple(2, 3) };

	cout << "s6" << endl;
	Csmaple arry6[3] = { Csmaple(3, 2), Csmaple(1, 4), 3 };

	cout << "s7" << endl;
	Csmaple *arry7[3] = { new Csmaple(2), new Csmaple(1, 2) };
	cout << "s8" << endl;
	Csmaple a;
	Csmaple b(a);
	Csmaple c = a;
	func1(a);
	cout<<func2().v<<endl;

	system("pause");
	return 0;
}