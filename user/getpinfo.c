#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if (argc != 2) {
    printf("Usage: getpinfo <pid>\n");
    exit(1);
  }

  int pid = atoi(argv[1]);
  struct pstat st;

  if (getpinfo(&st) < 0) {
    printf("getpinfo failed\n");
    exit(1);
  }

  for (int i = 0; i < NPROC; i++) {
    if (st.inuse[i] && st.pid[i] == pid) {
      printf("Process Info for PID %d:\n", pid);
      printf("Tickets: %d\n", st.lottery_tickets[i]);
      printf("pid: %d\n", st.pid[i]);
      printf("Executed: %d\n", st.times_executed[i]);
      exit(0);
    }
  }

  printf("Process with PID %d not found.\n", pid);
  exit(1);
}
