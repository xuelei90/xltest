#include <iostream>
using namespace std;

class A
{};

class B
{
public:
	int m_a;
	static int m_b;

	void printA()
	{
		cout << "printA" << endl;
	}
	//编译器编译如下
	//void printA(B* const this)
	//{
	//	cout << "printA" << endl;
	//}

	virtual void printB()
	{
		cout << "printB" << endl;
	}

	void printC()
	{
		cout << m_a << endl;
	}
	//编译器编译如下
	//void printC(B* const this)
	//{
	//	cout << this->m_a << endl;
	//}

	static void printD() //只能访问静态成员
	{
		//cout << m_a << endl;
		cout << m_b << endl;
	}
	//编译器编译如下
	//static void printD() //不生成this指针
	//{
	//	cout << m_a << endl;
	//}
};

void testNullClass()
{
	cout << sizeof(A) << endl; //1
}

void testNullPoint()
{
	B *p = NULL; //0地址
	p->printA(); //B::printA(NULL);
	p->printB(); //B::printB(NULL);	段错误
	p->printC(); //B::printC(NULL);	段错误
	
	B b;
	b.printA(); //B::printA(&b);
	b.printB(); //B::printB(&b);
	b.printD(); //B::printD();
}

void testArrayAddr()
{
	char *strName = "Hello";
	cout << sizeof(strName) << endl;
	cout << sizeof(*strName) << endl;
}

int main()
{
//	testNullClass();
//	testNullPoint();
	testArrayAddr();
}
