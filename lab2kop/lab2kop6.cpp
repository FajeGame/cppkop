#include<iostream>
using namespace std;

class IX
{
public:
	virtual void Fx1() = 0;
	virtual void Fx2() = 0;
	virtual void Fx3() = 0;
	virtual void Fx4() = 0;
};

class CA : public IX {
public:
	// Данные экземпляра
	double m_Fx2;
	double m_Fx3;
	double m_Fx4;

	// Реализация интерфейса IX
	virtual void Fx1() { cout << "CA::Fx1" << endl; };
	virtual void Fx2() { cout << m_Fx2 << endl; };
	virtual void Fx3() { cout << m_Fx3 << endl; };
	virtual void Fx4() { cout << m_Fx4 << endl; };

	// Конструктор
	CA(double d) {
		m_Fx2 = d * d;
		m_Fx3 = d * d * d;
		m_Fx4 = d * d * d * d;
	};
};

void foo(IX* pIX)
{
	pIX->Fx1();
	pIX->Fx2();
};

class CB : public IX {
public:
	// Реализация интерфейса IX
	virtual void Fx1() { cout << "CB::Fx1" << endl; };
	virtual void Fx2() { cout << "CB::Fx2" << endl; };
	virtual void Fx3() { cout << "CB::Fx3" << endl; };
	virtual void Fx4() { cout << "CB::Fx4" << endl; };
};

int main()
{
	// Создать экземпляр CA
	CA* pA = new CA(1.789);

	// Создать экземпляр CB
	CB* pB = new CB;

	// Получить указатель IX для CA
	IX* pIX = pA;
	foo(pIX);

	// Получить указатель IX для CB
	pIX = pB;
	foo(pIX);

	return 0;
};