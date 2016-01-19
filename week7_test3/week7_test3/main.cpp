#include <iostream>
#include <string>
using namespace std;
int main()
{
	string a1 = "wangjj";
	cout << a1.length() << endl;
	for (int i = 0; i < a1.length();i++)
	{
		cout << a1.at(i) << endl;
	}
	string a2("hello");
	a2 += a1;
	cout << a2 << endl;

	a2.append(a1);
	cout << a2 << endl;

	a1.append(a2, 5, a2.size());
	cout << a1 << endl;

	string a3("hello wangjj");
	string a4;
	a4 = a3.substr(6, 11);
	cout << a4 << endl;


	string s1("hello world");
	cout << s1.capacity() << endl;
	cout << s1.max_size() << endl;
	cout << s1.size() << endl;
	cout << s1.length() << endl;
	cout << s1.empty() << endl;
	cout << s1 << "aaa" << endl;
	s1.resize(s1.length() + 10);
	cout << s1.capacity() << endl;
	cout << s1.max_size() << endl;
	cout << s1.size() << endl;
	cout << s1.length() << endl;
	cout << s1 << "aaa" << endl;
	s1.resize(0);
	cout << s1.empty() << endl;


	string m1 = "wangjj";
	int a = m1.find("ng");
	cout << a << endl;
	int b = m1.find_first_of("j");
	int c = m1.find_last_of("j");
	cout << b << "  " << c << endl;
	int d = m1.find_first_not_of("wang");
	cout << d << endl;

	string b1("hello world");
	string b2("show insert");
	b1.insert(6, b2); // 将s2插入s1下标5的位置
	cout << b1 << endl;

	string c1("hello world");
	const char * p1 = c1.data();
	for (int i = 0; i < c1.length(); i++)
		printf("%c", *(p1 + i));


	cout << endl;
	string d1("hello world");
	int len = d1.length();
	char * p2 = new char[len + 1];
	d1.copy(p2, 5, 0);  
	p2[5] = 0;
	cout << p2 << endl;

	system("pause");
	return 0;
}