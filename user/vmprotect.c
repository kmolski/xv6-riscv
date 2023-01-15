#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int* ptr = malloc(sizeof(int));
  printf("Unprotected read: %d\n", *ptr);

  //mprotect((void*) ptr, 1);
  printf("UNREACHABLE: %d\n", *ptr);
  exit(1);
}
