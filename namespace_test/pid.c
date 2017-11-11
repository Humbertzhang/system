#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

#define STACKSIZE (1024*1024)

static char child_stack[STACKSIZE];
char * const child_args[] = {"/bin/bash", NULL};

int child_main(void *args) {
    printf("In son process.\n");
    sethostname("NewNamespace", 12);
    execv(child_args[0], child_args);
    return 1;
}

int main() {
    printf("Start process.\n");
    int child_pid = clone(child_main, child_stack + STACKSIZE, 
                        CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD, NULL);
    waitpid(child_pid, NULL, 0);
    printf("Exit...\n");
    return 0;
}
