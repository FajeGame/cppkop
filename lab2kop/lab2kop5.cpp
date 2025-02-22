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

class CA : public IX{
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

int main()
{
	// Создать 1-й экземпляр CA
	CA* pA1 = new CA(1.5);

	// Создать 2-й экземпляр CA
	CA* pA2 = new CA(2.75);

	return 0;
};