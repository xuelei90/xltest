#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
//  printf("hello strace\n");
  char buff[32];
//  strcpy(buff, "hello");
  strncpy(buff, "hello stdout\n", sizeof(buff));
  write(1, buff, sizeof(buff)); //stdout
  return 0;
}
