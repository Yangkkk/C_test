#include <iostream>
#include <string>
using namespace std;
int main()
{
	string s1("good");
	string s2("morning");
	s2.append(s1, 3, s1.size());
	cout << s2 << endl;
	system("pause");
	return 0;
}