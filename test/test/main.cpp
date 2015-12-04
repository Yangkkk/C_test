#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;
class Ctyre{
public:
	Ctyre()
	{
		cout << "Ctyre conductor" << endl;
	}
	~Ctyre(){
		cout << "Ctyre destructor" << endl;
	}
};
class  Cengine
{
public:
	Cengine(){
		cout << "engine conductor" << endl;
	}
	~Cengine(){
		cout << "engine destructor" << endl;
	}
};
class Ccar
{
public:
	Ccar(){
		cout << "Ccar conductor" << endl;
	}
	~Ccar(){
		cout << "Ccar desductor" << endl;
	}

private:
	Cengine engine;
	Ctyre tyre;
};
int main()
{
	Ccar car;
	system("pause");
	return 0;
}