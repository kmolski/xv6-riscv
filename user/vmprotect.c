#include "kernel/types.h"
#include "user/user.h"

void*
pgrounddown(void* addr)
{
  return (void*) (((uint64) addr) & ~((uint64) 4095));
}

int
main(int argc, char *argv[])
{
  printf("mprotect tests:\n");
  if (mprotect((void*) 0, -1337) != -1) {
    printf("  Negative length: FAIL\n");
    exit(1);
  } else {
    printf("  Negative length: OK\n");
  }

  if (mprotect((void*) 0, 0) != -1) {
    printf("  Zero length: FAIL\n");
    exit(1);
  } else {
    printf("  Zero length: OK\n");
  }

  if (mprotect((void*) 0x1337, 1) != -1) {
    printf("  Unaligned address: FAIL\n");
    exit(1);
  } else {
    printf("  Unaligned address: OK\n");
  }

  if (mprotect((void*) 0, 1) != -1) {
    printf("  Unmapped address: FAIL\n");
    exit(1);
  } else {
    printf("  Unmapped address: OK\n");
  }

  int* ptr = malloc(sizeof(int));
  *ptr = 0;

  int pid;
  if ((pid = fork()) == 0) {
    printf("  Unprotected write: %s\n", (*ptr = 42) == 42 ? "OK" : "FAIL");
    exit(0);
  } else {
    wait(0);
  }

  void* va = pgrounddown(ptr);
  if (mprotect(va, 1) == 0) {
    printf("  Invoke mprotect: OK\n");
  } else {
    printf("  Invoke mprotect: FAIL\n");
    exit(1);
  }

  int xstatus;
  if ((pid = fork()) == 0) {
    printf("  ptr write: %d\n", (*ptr = 2137));
    exit(1);
  } else {
    wait(&xstatus);
    if (xstatus == -1) { // kernel killed child
      printf("  Protected write: OK\n");
    } else {
      printf("  Protected write: FAIL\n");
      exit(1);
    }
  }

  printf("munprotect tests:\n");
  if (munprotect((void*) 0, -1337) != -1) {
    printf("  Negative length: FAIL\n");
    exit(1);
  } else {
    printf("  Negative length: OK\n");
  }

  if (munprotect((void*) 0, 0) != -1) {
    printf("  Zero length: FAIL\n");
    exit(1);
  } else {
    printf("  Zero length: OK\n");
  }

  if (munprotect((void*) 0x1337, 1) != -1) {
    printf("  Unaligned address: FAIL\n");
    exit(1);
  } else {
    printf("  Unaligned address: OK\n");
  }

  if (munprotect((void*) 0, 1) != -1) {
    printf("  Unmapped address: FAIL\n");
    exit(1);
  } else {
    printf("  Unmapped address: OK\n");
  }

  if (munprotect(va, 1) == 0) {
    printf("  Invoke munprotect: OK\n");
  } else {
    printf("  Invoke munprotect: FAIL\n");
    exit(1);
  }

  if ((pid = fork()) == 0) {
    printf("  Write after munprotect: %s\n", (*ptr = 69) == 69 ? "OK" : "FAIL");
    exit(1);
  } else {
    wait(&xstatus);
    if (xstatus == -1) { // kernel killed child
      printf("  Write after munprotect: FAIL\n");
      exit(1);
    }
  }

  exit(0);
}
