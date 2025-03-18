#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig) {
printf("\nCaught signal %d (Ctrl+C). Exiting gracefully...\n", sig);
exit(0); // Exit the program
}

int main() {

if (signal(SIGINT, handle_sigint) == SIG_ERR) {
perror("Error setting signal handler");
return 1;
}
printf("Program running. Press Ctrl+C to test signal handling.\n");

while (1) {
printf("Working...\n");
sleep(1); // Simulate some work
}
return 0;
}
