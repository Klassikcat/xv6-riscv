#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main(void) {
  struct pstat s;
  if (getpinfo(&s) < 0) {
    printf("Error retrieving process information.\n");
    exit(1);
  }
  printf("Process Information:\n");
  for (int i = 0; i < NPROC; i++) {
    if (s.inuse[i]) {
      printf("PID: %d, Tickets: %d, Executed: %d\n", s.pid[i], s.lottery_tickets[i], s.times_executed[i]);
    }
  }
}
