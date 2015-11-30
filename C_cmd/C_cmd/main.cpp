#include <stdio.h>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++){
		printf("%s\n", argv[i]);
	}
	system("pause");
	return 0;
}