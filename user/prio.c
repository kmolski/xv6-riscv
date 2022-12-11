#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    printf("ERROR: priority value is required!\n");
    exit(1);
  }
  int prio = atoi(argv[1]);
  settickets(prio);
  printf("Running with priority %d\n", prio);

  for (int i = 0; ; ++i) {}
  exit(0);
}
