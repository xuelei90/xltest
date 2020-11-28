#include <iostream>
using namespace std;

class Resource
{
public:
  Resource()
  {
    cout << __FUNCTION__ << endl;
  }
  ~Resource()
  {
    cout << __FUNCTION__ << endl;
  }
};

class Base
{
public:
  Base()
  {
    cout << __FUNCTION__ << endl;
  }
  virtual ~Base()
  {
    cout << __FUNCTION__ << endl;
  }
};

class SmartClass : public Base
{
public:
  SmartClass()
  {
    cout << __FUNCTION__ << endl;
  }
  ~SmartClass()
  {
    cout << __FUNCTION__ << endl;
  }
private:
  Resource r;
};

int main()
{
  SmartClass smart;
  return 0;
}
