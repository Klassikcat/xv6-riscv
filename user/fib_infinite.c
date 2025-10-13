#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user.h"

static uint
fibonacci_sequence(uint n) 
{
  if (n <= 1) return n;
  return fibonacci_sequence(n - 1) + fibonacci_sequence(n - 2);
}

int
main(int argc, char *argv[]) 
{
  int n = atoi(argv[1]);
  if (n < 0) {
    printf("Error: Please enter a non-negative number\n");
    exit(1);
  }
  while (1) {
    fibonacci_sequence(n);
  }
  exit(0);
}
