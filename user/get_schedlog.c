#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#define NUM_PROCS 3
#define SLEEP_TIME 300
#define INTERVAL 10

// TODO: Implement the final output printing
// using integer outputs
// e.g. "f{n / m}.{n mod n}"

static void 
get_schedule_log(int pid) 
{
  struct pstat st;
  getpinfo(&st);
  
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

static int*
dispatch_procs(int num_procs, int* tickets) 
{
  int* pids = malloc(sizeof(int) * num_procs);

  for (int i = 0; i < NUM_PROCS; i++) {
    int pid = fork();
    if (pid < 0) {
      printf("fork failed\n");
      exit(1);
    } else if (pid == 0) {
      settickets(tickets[i]);
      char nbuf[4], sleepbuf[4];
      uint n = 40;
      itoa(nbuf, n);
      itoa(sleepbuf, SLEEP_TIME);
      char *argv[] = {"fib", nbuf, sleepbuf, 0};
      printf(
        "Executed fib_infinite pid=%d with n=%d and sleep=%d\n", 
        getpid(), 
        n, 
        SLEEP_TIME
      );
      exec("fib_infinite", argv);
      exit(0);
    } else {
        // Parent process
        pids[i] = pid;
    }
  }
  return pids;
}

static void
interval_logger(int* pids)
{
  int elapsed_time = 0;
  while (1) {
    for (int i = 0; i < NUM_PROCS; i++) {
      get_schedule_log(pids[i]);
    }
    elapsed_time += 1;
    if (elapsed_time >= INTERVAL) {
      break;
    }
    sleep(SLEEP_TIME);
  }
}

int
main() {
  int tickets[NUM_PROCS] = {30, 20, 10};
  int* pids = dispatch_procs(NUM_PROCS, tickets);

  sleep(INTERVAL);
  interval_logger(pids);
  for (int i = 0; i < NUM_PROCS; i++) {
    kill(pids[i]);
  }
  free(pids);
  return 0;
}
