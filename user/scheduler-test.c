#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/pstat.h"
#include "kernel/param.h"

static int
fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

static void
dispatch_worker(void) {
    const int NUM_WORKERS = 3;
    int num_tickets[NUM_WORKERS] = {30, 20, 10}; // OSTEP Graph Assginment 

    for (int i = 0; i < NUM_WORKERS; i++) {
        if (fork() == 0) { // Child process
            settickets(num_tickets[i]);
            char *argv[] = {"fibonacci", "20", 0};
            exec("fibonacci", argv);
        } else { // Parent process
            printf("Worker %d started with %d tickets.\n", i, num_tickets[i]);
        }
    }
    for (int i = 0; i < NUM_WORKERS; i++) {
        wait(0);
    }
}

static void
display_graph(void) {
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

static void 
main(void) {
    int rounds = 5;
    for (int i = 0; i < rounds; i++) {
        printf("Iteration %d: Current Process Status\n", i);
        dispatch_worker();
        display_graph();
    }
}