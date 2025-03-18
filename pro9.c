#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h> 

void sigalrm_handler(int sig) {
printf("Child received SIGALRM signal (%d)\n", sig);
// Print signal number (14)
exit(0);
}

int main() {
pid_t pid = fork();
if (pid == 0) { 
signal(SIGALRM, sigalrm_handler);
printf("Child process running...\n");
while (1) { // Child runs indefinitely
sleep(1);
}
} else if (pid > 0) { // Parent process
printf("Parent sending SIGALRM to child (PID:%d)\n", pid); 
sleep(3); 
kill(pid, SIGALRM); // Parent sends SIGALRM tochild
wait(NULL); // Wait for the child to terminate
} else {
perror("fork failed");
return 1;
}
return 0;
}
