#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

int add(int a, int b)
{
  return a+b;
}

int main()
{
	printf("hello CentOS");
  printf("hello spacevim\n");
  int ninta = 0;
  int nrename = 0;
  int c = add(ninta, nrename);
  printf("c=%d\n", c);
  int ncount = add(nrename, c);
  cout << ncount << endl;
  string strTest;
  strTest.append("string");

	return 0;
}
