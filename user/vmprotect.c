#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  //if (mprotect(0x1337, 1) != -1) {
  //  printf("ERROR: mprotect: no error on unaligned address\n");
  //}

  //if (mprotect(0, 1) != -1) {
  //  printf("ERROR: mprotect: no error on unmapped address\n");
  //}

  int* ptr = malloc(sizeof(int));
  printf("Unprotected read: %d\n", *ptr);

  int pid;
  if ((pid = fork()) == 0) {
    printf("Unprotected read: %d\n", *ptr);
    exit(0);
  } else {
    wait(0);
  }

  //mprotect((void*) ptr, 1);
  if ((pid = fork()) == 0) {
    printf("UNREACHABLE: %d\n", *ptr);
    exit(1);
  } else {
    wait(0);
    printf("UNREACHABLE: %d\n", *ptr);
  }
  exit(1);
}
