#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user.h"

static uint
fibonacci_sequence(uint n) 
{
  if (n <= 1) return n;
  return fibonacci_sequence(n - 1) + fibonacci_sequence(n - 2);
}

static void 
get_schedule_log(int pid) 
{
  struct pstat st;
  int ret = getpinfo(&st);
  if (ret < 0) {
    printf("sys_getpinfo failed\n");
    exit(1);
  }
  
  // Find the process in the pstat array and print its info
  for (int i = 0; i < NPROC; i++) {
    if (st.inuse[i] && st.pid[i] == pid) {
      printf("Process %d: tickets=%d, executions=%d\n", 
             pid, st.lottery_tickets[i], st.times_executed[i]);
      return;
    }
  }
  printf("Process %d not found in process table\n", pid);
}

int
main(int argc, char *argv[]) 
{
  int n = atoi(argv[1]);
  if (n < 0) {
    printf("Error: Please enter a non-negative number\n");
    exit(1);
  }
  for (int i = 0; i <= n; i++) {
    fibonacci_sequence(i);
  }
  int pid = getpid();
  get_schedule_log(pid);
  exit(0);
}
