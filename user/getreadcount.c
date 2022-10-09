#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int x1 = getreadcount();
  int x2 = getreadcount();

  char buf[100];
  (void) read(4, buf, 1);
  int x3 = getreadcount();

  int i;
  for (i = 0; i < 1000; i++) {
    (void) read(4, buf, 1);
  }
  int x4 = getreadcount();

  fprintf(1, "XV6_TEST_OUTPUT %d %d %d\n", x2-x1, x3-x2, x4-x3);

  int y1 = getreadcount();

  int rc = fork();

  int total = 0;
  int j;
  for (j = 0; j < 100000; j++) {
    char buf[100];
    (void) read(4, buf, 1);
  }
  // https://wiki.osdev.org/Shutdown
  // (void) shutdown();

  if (rc > 0) {
    (void) wait(0);
    int y2 = getreadcount();
    total += (y2 - y1);
    fprintf(1, "XV6_TEST_OUTPUT %d\n", total);
  }
  exit(0);
}
