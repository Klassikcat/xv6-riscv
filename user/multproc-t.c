#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
main(void)
{
  int nprocs = 11;
  int pid;
  for(int i = 0; i < nprocs; i++) {
    pid = fork();
    if (pid < 0) {
      fprintf(2, "fork failed\n");
      exit(1);
    } else if (pid == 0) {
      char *argv[] = { "cpu-t", 0 };
      exec("cpu-t", argv);
      fprintf(2, "exec failed\n");
      exit(1);
    }
  }
  for(int i = 0; i < nprocs; i++) {
    wait(0);
  }
  exit(0);
}
