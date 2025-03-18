#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
pid_t pid1, pid2;
printf("Fork program starting\n");
pid1 = fork();
if (pid1 == -1)
{
perror("First fork failed");
exit(1);
} else if (pid1 == 0)
{
// Code executed by the first child
for (int i = 0; i < 5; i++) {
printf("Child 1: Displaying message %d\n", i + 1);
sleep(1); // Simulate some work
}
exit(0);
}
pid2 = fork();
if (pid2 == -1) {
perror("Second fork failed");
exit(1);
} else if (pid2 == 0) {
// Code executed by the second child
for (int i = 0; i < 3; i++) {
printf("Child 2: Displaying message %d\n", i + 1);
sleep(1); // Simulate some work
}
exit(0);
}
// Code executed by the parent process
printf("Parent process waiting for children to complete...\n");
wait(NULL); // Wait for any child to complete
wait(NULL); // Wait for the other child to complete
printf("Parent process: All child processes have completed.\n");
return 0;
}
