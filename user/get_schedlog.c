#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"
#include "kernel/pstat.h"
#define NUM_PROCS 3

void itoa(char *buf, uint n) {
  int i = 0;
  if (n == 0) {
    buf[i++] = '0';
    buf[i] = '\0';
    return;
  }
  char tmp[12];
  while (n > 0) {
    tmp[i++] = (n % 10) + '0';
    n /= 10;
  }
  int j = 0;
  while (i > 0) {
    buf[j++] = tmp[--i];
  }
  buf[j] = '\0';
}

static uint*
dispatch_procs(void) 
{
  unsigned int tickets[NUM_PROCS] = {30, 20, 10};
  unsigned int* pids = malloc(sizeof(int) * NUM_PROCS);

  // Fork all children first
  for (int i = 0; i < NUM_PROCS; i++) {
        int pid = fork();
        if (pid < 0) {
            printf("fork failed\n");
            exit(1);
        } else if (pid == 0) {
            settickets(tickets[i]);
            char nbuf[4];
            uint n = 40;
            char *argv[] = {"fib", nbuf, 0};
            itoa(nbuf, n);
            exec("fib", argv);
            exit(0);
        } else {
            // Parent process
            pids[i] = pid;
        }
  }
  return pids;
}


int
main() {
  dispatch_procs();
  for (int i = 0; i < NUM_PROCS; i++) {
    wait(0);
  }
  return 0;
}
