#include <stdio.h>
#include <stdlib.h>
using namespace std;
int MyCompare(const void *elmn1, const void *elmn2);
#define  num 5
int main()
{
	unsigned int an[num] = { 8, 123, 11, 10, 4 };
	qsort(an, num, sizeof(unsigned int), MyCompare);
	for (int i = 0; i < num; i++){
		printf("%d ", an[i]);
	}
	system("pause");



	return 0;
}
int MyCompare(const void* elmn1, const void* elmn2)
{
	unsigned int *p1, *p2;
	p1 = (unsigned int *)elmn1;
	p2 = (unsigned int *)elmn2;
	return(*p1 % 10) - (*p2 % 10);
}