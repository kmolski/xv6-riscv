#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  long num = *((long*) 0);
  printf("%lu", num);
  exit(0);
}
