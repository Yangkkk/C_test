#include <iostream>
#include <math.h>
using namespace std;

class CRectangle
{
public:
	CRectangle();
	~CRectangle();
	double Area(double &w, double &h){
		double area = w*h;
		return area;
	}
	double Perimeter(double &w, double &h){
		double perimeter = 2 * (w + h);
		return perimeter;
	}
	void Init(double &w_, double &h_){
		width = w_;
		height = h_;
	}
	double Area1(){
		return width*height;
	}
	double Perimeter1(){
		return 2 * (width + height);
	}

	//double A();
	//double wid;
	//double hei;
private:
	double width;
	double height;
};
CRectangle::CRectangle()
{
}

CRectangle::~CRectangle()
{
}


int main()
{
	double w, h;
	cin >> w >> h;
	CRectangle R;
	cout << R.Perimeter(w, h) <<"  "<< R.Area(w, h) << endl;
	R.Init(w, h);
	cout << R.Perimeter1() << "   " << R.Area1() << endl;
	cout << sizeof(CRectangle) << endl;
	cout << sizeof(double) << endl;
	printf("%d\n", 34 & 27);
	printf("%x\n", -12>>2);
	printf("%d\n", 26|14);
	printf("%d\n", 18^22);

	int *p = new int[12];
	cout << sizeof(p) << endl;

	int a = 3, b = 5;

	int & r = a;

	r = b;

	b = 7;

	cout << a << endl;

	system("pause");
	return 0;
}