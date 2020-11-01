#include <iostream>
#include <memory>

class CTest
{
public:
	CTest()
	{
		std::cout << "CTest()" << std::endl;
	}
	~CTest()
	{
		std::cout << "~CTest()" << std::endl;
	}
};

template<typename T>
class myptr
{
public:
	myptr():m_nCount(1)
	{
	}
private:
	static int m_nCount;
	T *ptr;
};

int main()
{
	std::shared_ptr<CTest> p1 = std::make_shared<CTest>();
	std::cout << "1 ref:" << p1.use_count() << std::endl;
	{
		std::shared_ptr<CTest> p2 = p1;
		std::cout << "2 ref:" << p1.use_count() << std::endl;
	}
	std::cout << "3 ref:" << p1.use_count() << std::endl;

	return 0;
}
