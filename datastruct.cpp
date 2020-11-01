#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

template<typename T>
class CMyList
{
public:
	struct Node
	{
		T data;
		Node *next;
		//Node(const T &d, const Node *p):data(d),next(p){}
	};

	//
	CMyList():m_pHead(NULL),m_iLen(0){}

	//基本
	int size() const //长度
	{
		return m_iLen;
	}
	bool empty() const //是否空
	{
		if (m_pHead == NULL)
			return true;
		else
			return false;
	}

	//增
	bool insert(Node *pPos, const T &data) //任意位置
	{
		if (pPos == m_pHead) //头插
		{
			Node *pNew = new Node();
			pNew->data = data;
			pNew->next = m_pHead;
			m_pHead = pNew;
			m_iLen += 1;
			return true;
		}
		else //其他位置插
		{
			Node *p = m_pHead;
			while (p != NULL)
			{
				if (p == pPos)
				{
					Node *pNew = new Node();
					pNew->data = data;
					pNew->next = p->next;
					p->next = pNew;
					m_iLen += 1;
					return true;
				}
				p = p->next;
			}
		}
		return false;
	}
	bool push_front(const T &data) //头增
	{
		return insert(m_pHead, data);
	}

	//删
	bool erase(Node *pPos) //按位置	
	{
		Node *p = m_pHead;
		while (p != NULL)
		{
			if (p->next == pPos)
			{
				p->next = pPos->next;
				delete pPos;
				m_iLen--;
				return true;
			}
			p = p->next;
		}
		return false;
	}
	void remove(const T &data) //按数据删相等的
	{
		Node *p = m_pHead;
		while (p != NULL)
		{
			if (p->next->data == data)
			{
				Node *q = p->next;
				p->next = q->next;
				delete q;
				m_iLen--;
			}
			p = p->next;
		}
	}
	void clear() //清空所有
	{
		while (m_pHead != NULL)
		{
			Node *p = m_pHead;
			m_pHead = p->next;
			delete p;
		}
		m_iLen = 0;
	}

	//查
	Node* get_ptr(const T &data) //获取指定元素指针
	{
		Node *p = m_pHead;
		while (p != NULL)
		{
			if (p->data == data)
			{
				return p;
			}
			p = p->next;
		}
		return NULL;
	}
	void travel() //遍历
	{
		Node *p = m_pHead;
		while (p != NULL)
		{
			cout << p->data << endl;
			p = p->next;
		}
	}

private:
	Node *m_pHead;
	int m_iLen;
};

void testMyList()
{
	CMyList<int> clMyList;
	clMyList.push_front(1);
	clMyList.push_front(2);
	clMyList.push_front(3);

	CMyList<int>::Node *pNode2 = clMyList.get_ptr(2);
	clMyList.insert(pNode2, 10);

	cout << "len:" << clMyList.size() << endl;
	clMyList.travel();

	clMyList.clear();
	cout << "len:" << clMyList.size() << endl;
	clMyList.travel();

	clMyList.push_front(4);
	clMyList.push_front(5);
	clMyList.push_front(6);
	cout << "len:" << clMyList.size() << endl;
	clMyList.travel();

	CMyList<int>::Node *pNode5 = clMyList.get_ptr(5);
	clMyList.erase(pNode5);
	cout << "len:" << clMyList.size() << endl;
	clMyList.travel();

	clMyList.push_front(7);
	clMyList.push_front(4);
	clMyList.push_front(8);
	cout << "len:" << clMyList.size() << endl;
	clMyList.travel();

	clMyList.remove(4);
	cout << "len:" << clMyList.size() << endl;
	clMyList.travel();
}

//快速排序 O(n*log2 n)
template<typename T>
void quickSort(T *arr, int size)
{
	if (size <= 1)
		return;

	int move = 0;
	T mid = arr[0];	//第一个元素做中间值
	for (int i=1; i<size; i++) //都和中间值比较
	{
		if (arr[i] < mid) //小的放左边
		{
			T little = arr[i];
			for (int j=i-1; j>=0; j--)
			{
				arr[j+1] = arr[j];
			}
			arr[0] = little;
			move++; //中间值移动了多少次
		}
	}

	quickSort(arr, move);
	quickSort(arr+move+1, size-move-1);
}

void testSort()
{
	double arr[] = {3,2,5,6,4,7,8,0,9,1,20,18,98,45,33.1,33.5,33.2};
	quickSort(arr, sizeof(arr)/sizeof(double));
	for (int i=0; i<sizeof(arr)/sizeof(double); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void print(vector<int> &vValue)
{
	cout << "size:" << vValue.size() 
		//<< " max_size:" << vValue.max_size() 
		<< " capacity:" << vValue.capacity() 
		<< endl;

	vector<int>::iterator it;
	for (it = vValue.begin(); it != vValue.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void print(list<int> &vValue)
{
	cout << "size:" << vValue.size() 
		//<< " max_size:" << vValue.max_size() 
		<< endl;

	list<int>::iterator it;
	for (it = vValue.begin(); it != vValue.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void print(map<string, int> &vValue)
{
	cout << "size:" << vValue.size() 
		//<< " max_size:" << vValue.max_size() 
		<< endl;

	map<string, int>::iterator it;
	for (it = vValue.begin(); it != vValue.end(); it++)
	{
		cout << it->first << "->" << it->second << " ";
	}
	cout << endl;
}

void testVector()
{
	vector<int> vValue;
	vValue.push_back(1);
	vValue.push_back(2);
	vValue.push_back(3);
	print(vValue);

	vValue.resize(5);
	print(vValue);

	vValue.at(3) = 4;
	print(vValue);
//	cout << vValue.at(5) << endl; //throw
	cout << vValue[5] << endl; //危险
	cout << vValue[6] << endl; //超出容量

	vValue.push_back(8);
	vValue.push_back(9);
	print(vValue);

	vector<int>::iterator itb = vValue.begin();
	vValue.insert(itb+2, 30);
	print(vValue);

	cout << "erase---\n";
	vector<int>::iterator ite = vValue.end();
	vValue.erase(ite-1);
	print(vValue);

	vValue.pop_back(); //vector只有尾删，适合做栈
	print(vValue);

	vValue.clear();
	print(vValue);
}

void testList()
{
	list<int> vValue;
	vValue.push_back(1);
	vValue.push_back(2);
	vValue.push_back(3);
	print(vValue);

	vValue.resize(5);
	print(vValue);

	//不支持随机访问

	vValue.push_back(8);
	vValue.push_back(9);
	print(vValue);

	list<int>::iterator itb = vValue.begin();
	++itb; //迭代器只能自增（也不能+1）
	vValue.insert(itb, 11);
	print(vValue);

	list<int>::iterator ite = vValue.end();
	vValue.erase(--ite);//只能自减
	print(vValue);

	vValue.pop_front(); //list双向链表 头/尾删，可以做栈/队列
	print(vValue);

	vValue.sort();
	print(vValue);

	vValue.clear();
	print(vValue);
}

void testAddAdd()
{
	testVector();
	int i = 0, j = 0;
	cout << ++i << " " << j++ << endl;

	int i2 = 0, j2 = 0;
	int x = ++i2; //先自增 再赋值给x（i=i+1;x=i）
	int y = j2++;	//先赋值给y 再自增（y=j;j=j+1）
	cout << i2 << " " << j2 << endl;
	cout << x << " " << y << endl;
}

void testMap()
{
	map<string, int> mStu;
	mStu.insert(pair<string, int>("xue", 30));
	mStu.insert(pair<string, int>("liu", 29));
	mStu.insert(pair<string, int>("mei", 27));
	mStu.insert(pair<string, int>("mei", 999)); //key重复，无效数据
	mStu.insert(pair<string, int>("aa", 88));
	mStu.insert(pair<string, int>("zz", 19));
	print(mStu); //红黑树 自动排序

	cout << mStu["mei"] << endl; //直接通过key访问

	map<string, int>::iterator it = mStu.begin();
	mStu.erase(++it); //迭代器只能自增/自减
	print(mStu);

	map<string, int>::iterator itf = mStu.find("zz");
	if (itf != mStu.end()) //末尾标志
	{
		cout << itf->second << endl;
	}
}

void testSet()
{
	set<int> sValue; //红黑树 自动排序
	sValue.insert(2);
	sValue.insert(6);
	sValue.insert(6); //重复，无效数据
	sValue.insert(3);
	for (set<int>::iterator it = sValue.begin(); it != sValue.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void testAlgori()
{
	vector<int> vValue;
	vValue.push_back(3);
	vValue.push_back(5);
	vValue.push_back(2);
	vValue.push_back(9);
	vValue.push_back(8);
	print(vValue);

	vector<int>::iterator itf = std::find(vValue.begin(), vValue.end(), 2);
	cout << *++itf << endl; //下一个元素

	vector<int>::iterator itNewEnd = std::remove(vValue.begin(), vValue.end(), 2);
	print(vValue); //std::remove函数没有更新容器尾指针（导致迭代器失效）
	for (vector<int>::iterator it = vValue.begin(); it != itNewEnd; it++)
	{
		cout << *it << " ";
	}
	cout << endl;

	std::sort(vValue.begin(), itNewEnd); //得用新尾，不能用end了
	print(vValue); //错误输出（多输出一个）

	cout << "min:" << std::min(10,30) << endl;
}

void testIterNouse()
{
	vector<int> vValue;
	vValue.push_back(1);
	vValue.push_back(2);
	vValue.push_back(3);
	vValue.push_back(3);
	vValue.push_back(4);
	print(vValue);

	cout << "----------------" << endl;
	//删除所有大于等于3的元素（没有现成函数）
	for (vector<int>::iterator it = vValue.begin(); it != vValue.end(); )
	{
		cout << "访问到" << *it << endl; //很容易落一个
		if (*it >= 3)
		{
			vValue.erase(it); //元素前移，所以当前位置就是下一个元素，不需++
		}
		else
		{
			++it;
		}
	}
	
	cout << "----------------" << endl;
	print(vValue);

	cout << "----------------" << endl;
	//删除所有元素（clear不会清理堆内存）倒着删不易出错且效率高
	for (vector<int>::iterator it = vValue.end()-1; it != vValue.begin()-1; --it)
	{
		cout << "删除" << *it << endl;//或delete
		vValue.erase(it);
	}
	print(vValue);
}

int main()
{
	//testMyList();
	//testSort();
	//testVector();
	//testAddAdd();
	//testList();
	//testMap();
	//testSet();
	//testAlgori();
	testIterNouse();
	return 0;
}
