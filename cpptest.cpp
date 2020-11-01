#include <string.h>
#include <iostream>
#include <string>
#include <exception>

class CInformation
{
public:
	CInformation():m_count(2){}
	~CInformation()
	{
		std::cout << m_szName  << " len:" << strlen(m_szName) << " count:" << m_count << std::endl;
	}
	
	bool SetName(const char *p_lpName);
	bool SetAge(int p_iAge);
	int GetAge() const	//不能修改成员变量（可以访问）
	{
		return m_iAge;
	}

	static int GetVersion() //没有this指针，只能访问静态成员变量
	{
		return m_version;
	}
	static int m_version;	//所有对象共享

private:
	char m_szName[8+1];
	int m_iAge;
	const int m_count; 		//不能被修改
};

int CInformation::m_version = 2;

bool CInformation::SetName(const char *p_lpName)
{
	strncpy(m_szName, p_lpName, sizeof(m_szName)); //ncpy安全
	m_szName[sizeof(m_szName)-1] = '\0';	//末尾手动置'\0'
	return true;
}

void testClass()
{
	CInformation clInformation1;
	clInformation1.SetName("Libai");

	CInformation clInformation2; //后构造的先析构
	clInformation2.SetName("Libai123456789");

	int age = clInformation2.GetAge();
	std::cout << "age:" << age << std::endl;

	std::cout << "verion:" << CInformation::GetVersion() << std::endl; //只能用类/命名空间访问
}

class CMyString
{
public:
	CMyString(const char *p_lpStr = NULL)
	{
		if (p_lpStr == NULL)
		{
			m_lpData = new char[1];
			m_lpData[0] = '\0';
		}
		else
		{
			m_lpData = new char[strlen(p_lpStr)+1];
			strcpy(m_lpData, p_lpStr);
		}
		std::cout << "构造：" << m_lpData << std::endl;
	}

	CMyString(const CMyString &p_refOther)
	{
		m_lpData = new char[strlen(p_refOther.m_lpData)+1];
		strcpy(m_lpData, p_refOther.m_lpData);
		std::cout << "拷贝构造：" << m_lpData << std::endl;
	}

	CMyString & operator=(const CMyString &p_refOther)
	{
		if (this == &p_refOther)
			return *this;

		delete []m_lpData;
		m_lpData = new char[strlen(p_refOther.m_lpData)+1];
		strcpy(m_lpData, p_refOther.m_lpData);
		std::cout << "赋值：" << m_lpData << std::endl;
		return *this;
	}

	~CMyString()
	{
		delete []m_lpData;
	}

private:
	char *m_lpData;
};

void testString()
{
	CMyString clStrTest1("CMyString");
	CMyString clStrTest2 = clStrTest1;
	CMyString clStrTest3;
	clStrTest3 = clStrTest1;

	//std::string
	std::string strTest1("string");
	std::string strTest2 = strTest1;
	std::cout << strTest1 << " " << strTest2 << std::endl;
	
	std::string s1 = "abcdefghijk";
	s1[10] = 'x';
	std::cout << s1 << std::endl;
	//插入
	s1.insert(5, "TTT"); 
	std::cout << s1 << std::endl;
	//删除
	s1.erase(5, 2);	
	std::cout << s1 << std::endl;
	//子串
	std::string s2 = s1.substr(5, 5); 
	std::cout << s2 << std::endl;
	//查找
	int pos = s1.find("ghi", 3); //找不到返回无穷大
	if (pos < s1.length()) 
	{
		std::cout << "find:" << pos << std::endl;
	}
	//从后向前查找
	std::string st = "1111111111";			//10个字符
	std::cout<< st.rfind("1111",9) << std::endl;	//从第9个位置向前查找，返回6
	std::cout<< st.rfind("1111",7) << std::endl;	//从第7个位置向前查找，返回6
	std::cout<< st.rfind("1111",5) << std::endl;	//从第5个位置向前查找，返回5
	std::cout<< st.rfind("1111",2) << std::endl;	//从第2个位置向前查找，返回2
	int pos2 = s1.rfind("ghi", 3);//3从第几个位置开始
	if (pos2 < s1.length()) 
	{
		std::cout << "rfind:" << pos2 << std::endl;
	}
	//共同具有的字符
	std::string str1 = "first second second third";
	std::string str2 = "asecond";
	int index = str1.find_first_of(str2); //'s'字符 索引3
	std::cout << index << std::endl;
}

class CPeople
{
public:
	CPeople(std::string &strName, int iAge)
		:m_strName(strName),m_iAge(iAge)
	{
		std::cout << "CPeople()" << std::endl;
	}
	~CPeople()
	{
		std::cout << "~CPeople()" << std::endl;
	}
	void ShowPeople()
	{
		std::cout << "CPeople:ShowPeople() name:" << m_strName << " age:" << m_iAge << std::endl;
	}
	void Display()
	{
		std::cout << "CPeople:Display() name:" << m_strName << " age:" << m_iAge << std::endl;
	}

protected:
	std::string m_strName;
	int m_iAge;
};

class CStudent : public CPeople
{
public:
	CStudent(std::string &strName, int iAge, int iGrade):
		CPeople(strName, iAge),
		m_iGrade(iGrade)
	{
		std::cout << "CStudent()" << std::endl;
	}
	~CStudent()
	{
		std::cout << "~CStudent()" << std::endl;
	}
	void Display()
	{
		std::cout << "CStudent:Display() name:" << m_strName << " age:" << m_iAge << " grade:" << m_iGrade << std::endl;
	}

private:
	int m_iGrade;
};

void testSubClass()
{
	std::string strNameX = "XiaoMing";
	CPeople clPeo(strNameX, 44);
	clPeo.ShowPeople();
	
	//子类
	std::string strNameZ = "ZhangSan";
	CStudent clStu(strNameZ, 23, 2);
	clStu.ShowPeople();//调用基类public函数 很常见
	clStu.Display();
}

class A
{
public:
	A(int a):m_a(a){}
	void display(){std::cout << "m_a=" << m_a << std::endl;}
public:
	int m_a;
};
class B: public A
{
public:
	B(int a, int b):A(a),m_b(b){}
	void display(){std::cout << "m_a=" << m_a << " m_b=" << m_b << std::endl;}
public:
	int m_b;
};

void testUpCast()
{
	//向上转型安全（调用原类函数）
	//1.派生类对象赋值给基类对象
	A a(1);
	B b(2,22);
	a = b;	//拷贝对象内存过去，多余的成员变量被丢掉
	a.display();	//原函数&新值
	std::cout << a.m_a << std::endl;
	//b = a; #向下转型报错

	//2.派生类指针赋值给基类指针
	A *pa = new A(1);
	A *ptmp = pa;
	B *pb = new B(2,22);
	pa = pb; //与对象变量之间的赋值不同的是，对象指针之间的赋值并没有拷贝对象的成员，也没有修改对象本身的数据，仅仅是改变了指针的指向
	//pb = pa; #向下转型报错
	pa->display();	//原函数&新值
	std::cout << ptmp->m_a << std::endl;
	std::cout << pa << " " << pb << std::endl;
	//编译器通过指针来访问成员变量，指针指向哪个对象就使用哪个对象的数据；编译器通过指针类型来访问成员函数，指针属于哪个类的类型就使用哪个类的函数。（有点不伦不类）

	//3.将派生类引用赋值给基类引用
	//与指针结果一样
}

class People
{
public:
	People(const char *szName, int iAge)
	{
		strncpy(m_szName, szName, sizeof(m_szName)-1);
		m_szName[sizeof(m_szName)-1] = '\0';
		m_iAge = iAge;
	}
	void show()
	{
		std::cout << m_szName << "是我" << m_iAge << "岁了，是个无业游民" << std::endl;
	}
	virtual void display()
	{
		std::cout << m_szName << "今年" << m_iAge << "岁了，是个无业游民" << std::endl;
	}
	virtual ~People()
	{
		std::cout << "~People()" << std::endl;
	}
protected:
	char m_szName[16+1];
	int m_iAge;
};

class Coder : public People
{
public:
	Coder(const char *szName, int iAge, int iSalary):
		People(szName, iAge),
		m_iSalary(iSalary)
	{
	}
	void show()
	{
		std::cout << m_szName << "是我" << m_iAge << "岁了，薪资" << m_iSalary << std::endl;
	}
	void display()
	{
		std::cout << m_szName << "今年" << m_iAge << "岁了，薪资" << m_iSalary << std::endl;
	}
	~Coder()
	{
		std::cout << "~Coder()" << std::endl;
	}
private:
	int m_iSalary;
};

void testVirtual()
{
	std::cout << "正常调用-------" << std::endl;
	People xue("xuelei", 30);
	xue.display();
	Coder liu("Liu", 29, 13000);
	liu.display();
	Coder zhang("Zhang", 32, 20000);

	//People *pxue = &xue; 	//基类指针->基类对象
	//pxue->display();			//肯定是基类函数/变量

	std::cout << "多态调用-------" << std::endl;
	//指针
	People *pBase = &liu;	//基类指针->派生类对象
	pBase->show();				//普通函数，依然调用基类函数
	pBase->display();			//virtual函数，调用派生类函数（目的实现了）
	//Coder *p1 = &xue; 		//#向下转型依然报错
	pBase = &zhang;				//基类指针改->另一个派生类对象
	pBase->display();			//virtual函数，调用另一个派生类函数（另一个目的实现了）

	//引用
	People &refliu = liu;
	refliu.display();			//virtual函数，调用派生类函数（目的实现了）
	//refliu = zhang; 	//最好不要这么用，因为它偷偷改了liu的值，你却不知道
	//refliu.display();

	std::cout << "赋值调用-------" << std::endl;
	//直接赋值
	People liu2 = liu;
	liu2.display();				//virtual函数，调用基类函数（实现不了目的）
}

void testVirDestrutor()
{
	People *pa = new Coder("Test", 24, 12000);
	delete pa; //虚析构函数才能调对派生类析构
}

class CNormal
{
public:
	void SetData(int data){m_data=data;}
private:
	int m_data;
};

class CVirtual
{
public:
	virtual void SetData(int data) {m_data=data;}
	//void ShowVirtualTable() {std::cout << this->__vptr << std::endl;}
private:
	int m_data;
	int m_data2;
};

void testVirtualTable()
{
	CNormal normal;
	normal.SetData(1);
	std::cout << sizeof(normal) << std::endl; //4byte

	CVirtual vir;
	vir.SetData(1);
	std::cout << sizeof(vir) << std::endl;	//8+8=16byte 跟结构体一样是8字节对齐

	char *p = NULL;
	std::cout << sizeof(p) << std::endl;	//8byte
}

template<typename T>
void swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<typename T1, typename T2>
class Point
{
public:
	T1 GetX() const {return m_x;}
	void SetX(T1 x);
private:
	T1 m_x;
	T2 m_y;
};

template<typename T1, typename T2>
void Point<T1, T2>::SetX(T1 x)
{
	m_x = x;
}

void testTemplate()
{
	int n1 = 10, n2 = 20;
	swap(n1, n2);
	std::cout << n1 << " " << n2 << std::endl;

	float f1 = 11.1, f2 = 22.2;
	swap(f1, f2);
	std::cout << f1 << " " << f2 << std::endl;

	Point<int, float> p1;
	p1.SetX(87);
	int x = p1.GetX();
	std::cout << x << std::endl;
}

void throwFun()
{
	std::cout << "正常" << std::endl;
	throw "异常";
	std::cout << "到不了" << std::endl;
}

void testException()
{
	std::string str = "http://www.baitu.com";
	try
	{
		char ch1 = str[100]; //不可预判的错误
		std::cout << ch1 << std::endl;
	}catch(std::exception e)
	{
		std::cout << "exp1" << std::endl;
	}

	try
	{
		char ch2 = str.at(100);	//抛出std::exception类异常
		std::cout << ch2 << std::endl;
		std::cout << "不会被执行" << std::endl;
	}catch(std::exception &e) //捕获异常
	{
		std::cout << "exp2" << std::endl;
	}

	try
	{
		throwFun();	//抛出自定义异常
	}catch(const char* &e) //「在运行阶段将实参和形参匹配」
	{
		std::cout << "exp3" << std::endl;
	}

	std::cout << "试试看" << std::endl;
}

int main()
{
	//testClass();
	//testString();
	//testSubClass();
	//testUpCast();
	//testVirDestrutor();
	//testVirtualTable();
	//testTemplate();
	testException();
	return 0;
}

