#include<iostream>
using namespace std;

class First {
public:
	int x;
	First(int fx) {
		x = fx;
	};
	virtual int calc() {
		return x;
	};
	void print(string text) {
		std::cout << text << calc() << std::endl;
	};
};
class Second : public First {
public:
	Second(int fx) : First(fx) {};
	virtual int calc() {
		return x * x;
	};
};
class Third : public Second {
public:
	Third(int fx) : Second(fx) {};
	virtual int calc() {
		return x * x * x;
	};
};

int main()
{
	First z(1);
	z.print("class First: ");

	Second x(3);
	x.print("class Second: ");

	Third y(5);
	y.print("class Third: ");
	return 0;
}