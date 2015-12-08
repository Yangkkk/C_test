#include <iostream>
#include <string>
using namespace std;
int main()
{
	char a[3] = { 'a','b','c'};
	string s(a,a+3);
	cout << s << endl;

	string s1;
	s1 = "good luck";
	cout << s1.c_str() << endl;
	//char a[] = s1.c_str();
	cout << s1 << endl;
	char a1[6] = "abcde";
	cout << sizeof(a1) << endl;
	int b = s1.size();
	cout << b << endl;

	system("pause");
	return 0;
}