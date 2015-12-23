#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
class CShape{
public:
	virtual double Area() = 0;
	virtual void PrintInfo() = 0;
};
class CRectangle :public CShape{
public:
	int w, h;
	virtual double Area();
	virtual void PrintInfo();
};
class CCirle :public CShape{
public:
	int r;
	virtual double Area();
	virtual void PrintInfo();
};
class CTriangle :public CShape{
public:
	int a,b,c;
	virtual double Area();
	virtual void PrintInfo();
};
double CRectangle::Area(){
	return w*h;
}
void CRectangle::PrintInfo(){
	cout << "Rectangle:" << Area() << endl;
}
double CCirle::Area(){
	return 3.14*r*r;
}
void CCirle::PrintInfo(){
	cout << "Circle:" << Area() << endl;
}
double CTriangle::Area(){
	double p = (a + b + c) / 2.0;
	return sqrt(p*(p - a)*(p - b)*(p - c));
}
void CTriangle::PrintInfo(){
	cout << "Triangle:" << Area() << endl;
}

CShape *pShapes[100];
int myCompare(const void* s1, const void* s2){
	double a1, a2;
	CShape* *p1;
	CShape* *p2;
	p1 = (CShape* *)s1;
	p2 = (CShape* *)s2;
	a1 = (*p1)->Area();
	a2 = (*p2)->Area();
	if (a1 < a2){
		return -1;
	}
	else if (a2 < a1){
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	int i, n;
	CRectangle *pr;
	CCirle *pc;
	CTriangle *pt;
	cin >> n;
	for (i = 0; i < n; ++i){
		char c;
		cin >> c;
		switch (c)
		{
		case 'r':
			pr = new CRectangle;
			cin >> pr->w >> pr->h;
			pShapes[i] = pr;
			break;
		case 'c':
			pc = new CCirle;
			cin >> pc->r;
			pShapes[i] = pc;
			break;
		case 't':
			pt = new CTriangle;
			cin >> pt->a >> pt->b >> pt->c;
			pShapes[i] = pt;
			break;
		default:
			break;
		}
	}
	qsort(pShapes, n, sizeof(CShape*), myCompare);
	for (i = 0; i < n; i++){
		pShapes[i]->PrintInfo();
	}
	system("pause");
	return 0;
}