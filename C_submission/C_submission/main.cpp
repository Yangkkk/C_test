#include <iostream>
#include<string>
#include<cstdio>
using namespace std;
class Student{
private:
	int age, g1, g2, g3, g4;
	int average;
	char name[100], a, num[100];
public:
	void input(){
		cin.getline(name, 100, ',');
		cin >> age;
		a = getchar();
		cin.getline(num, 100, ',');
		cin >> g1 >> a >> g2 >> a >> g3 >> a >> g4;
	}
	void ave(){
		average = ((g1 + g2 + g3 + g4) / 4);
	}
	void output(){
		cout << name << a << age << a << num << a << average;
	}
};
int main(){
	Student s;
	s.input();
	s.ave();
	s.output();
	//system("pause");
	return 0;
}

