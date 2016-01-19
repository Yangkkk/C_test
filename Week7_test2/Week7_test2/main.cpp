#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class CStudent{
public:
	char szName[20];
	int nsCore;
};

int main(){
	CStudent s;
	ofstream Outfile("student.txt", ios::app | ios::out);
	while (cin>>s.szName>>s.nsCore)
	{
		if (_stricmp(s.szName,"exit")==0)
		{
			break;
		}
		Outfile.write((char *)&s, sizeof(s));
	}
	Outfile.close();
	return 0;
}