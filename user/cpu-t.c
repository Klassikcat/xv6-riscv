#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void
main(void) {
  long a = 0;
  for(long i=0; i<1000000000L; i++) { a += i*i; }
  printf("done!");
}
