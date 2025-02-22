#include <iostream>
using namespace std;
int main()
{
	int a = 5, b = 0;
	int* pa;  pa = &a;
	cout << "a = " << a << endl;
	cout << " * pa = " << *pa << endl;
	cout << "pa = " << pa << endl;
	b = *pa - 3;
	cout << "b = " << b << endl;
	if (a == *pa) *pa = b;
	cout << "a = " << a << endl;
	cout << " * pa = " << *pa << endl;
	b = 6;  pa = &b;
	cout << "b = " << b << endl;
	cout << " * pa = " << *pa << endl;
	cout << "a = " << a << endl;
	return 0;
}
