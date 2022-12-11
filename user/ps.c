#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"

void
ps()
{
  struct pstat pstat;
  getpinfo(&pstat);

  printf("PID TCKTS TICKS\n");
  for (int i = 0; i < NPROC; ++i) {
    if (pstat.inuse[i]) {
      printf("%d   %d     %d\n", pstat.pid[i], pstat.tickets[i], pstat.ticks[i]);
    }
  }
}

int
main(int argc, char *argv[])
{
  ps();
  exit(0);
}
