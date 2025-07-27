
struct pstat {
  int inuse[NPROC];   // whether this slot of the process table is in use (1 or 0)
  int lottery_tickets[NPROC]; // the number of tickets this process has
  int pid[NPROC];     // the PID of each process 
  int times_executed[NPROC];
};
