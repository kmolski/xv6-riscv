#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"

void
print_stats()
{
  struct pstat pstat;

  for (int i = 0; i < 300; ++i) {
    int up = uptime();

    getpinfo(&pstat);
    for (int i = 0; i < NPROC; ++i) {
      if (pstat.inuse[i]) {
        printf("%d,%d,%d,%d\n", up, pstat.pid[i], pstat.tickets[i], pstat.ticks[i]);
      }
    }

    sleep(10);
  }
}

int prio_pids[3] = {-1};

int
main(int argc, char *argv[])
{
  if (fork() == 0) {
    prio_pids[0] = getpid();
    char* args[] = {"prio", "10"};
    exec("prio", args);
  }

  if (fork() == 0) {
    prio_pids[1] = getpid();
    char* args[] = {"prio", "20"};
    exec("prio", args);
  }

  if (fork() == 0) {
    prio_pids[2] = getpid();
    char* args[] = {"prio", "30"};
    exec("prio", args);
  }

  print_stats();

  kill(prio_pids[0]);
  kill(prio_pids[1]);
  kill(prio_pids[2]);

  exit(0);
}
