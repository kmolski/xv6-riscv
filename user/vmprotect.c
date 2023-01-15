#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("mprotect tests:\n");
  if (mprotect((void*) 0, -1337) != -1) {
    printf("  Negative length: FAIL\n");
  } else {
    printf("  Negative length: OK\n");
  }

  if (mprotect((void*) 0, 0) != -1) {
    printf("  Zero length: FAIL\n");
  } else {
    printf("  Zero length: OK\n");
  }

  if (mprotect((void*) 0x1337, 1) != -1) {
    printf("  Unaligned address: FAIL\n");
  } else {
    printf("  Unaligned address: OK\n");
  }

  if (mprotect((void*) 0, 1) != -1) {
    printf("  Unmapped address: FAIL\n");
  } else {
    printf("  Unmapped address: OK\n");
  }

  int* ptr = malloc(sizeof(int));
  *ptr = 0;

  int pid;
  if ((pid = fork()) == 0) {
    printf("  Unprotected read: %s\n", (*ptr == 0) ? "OK" : "FAIL");
    exit(0);
  } else {
    wait(0);
  }

  int xstatus;
  mprotect((void*) ptr, 1);
  if ((pid = fork()) == 0) {
    printf("  ptr value: %d\n", *ptr);
    exit(1);
  } else {
    wait(&xstatus);
    if (xstatus == -1) { // kernel killed child
      printf("  Protected read: OK\n");
    } else {
      printf("  Protected read: FAIL\n");
    }
  }

  printf("munprotect tests:\n");
  if (munprotect((void*) 0, -1337) != -1) {
    printf("  Negative length: FAIL\n");
  } else {
    printf("  Negative length: OK\n");
  }

  if (munprotect((void*) 0, 0) != -1) {
    printf("  Zero length: FAIL\n");
  } else {
    printf("  Zero length: OK\n");
  }

  if (munprotect((void*) 0x1337, 1) != -1) {
    printf("  Unaligned address: FAIL\n");
  } else {
    printf("  Unaligned address: OK\n");
  }

  if (munprotect((void*) 0, 1) != -1) {
    printf("  Unmapped address: FAIL\n");
  } else {
    printf("  Unmapped address: OK\n");
  }

  munprotect((void*) ptr, 1);
  if ((pid = fork()) == 0) {
    printf("  Read after munprotect: %s\n", (*ptr == 0) ? "OK" : "FAIL");
    exit(1);
  } else {
    wait(&xstatus);
    if (xstatus == -1) { // kernel killed child
      printf("  Protected read: FAIL\n");
    }
  }

  exit(0);
}
