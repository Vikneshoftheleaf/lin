#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h> 
#define PIPE_NAME "/tmp/calc_fifo"
void process_request(const char *request) {
int num1, num2;
char op;
if (sscanf(request, "%d%c%d", &num1, &op, &num2) == 3) {
int result;
switch(op) {
case '+': result = num1 + num2; break;
case '-': result = num1 - num2; break;
case '*': result = num1 * num2; break;
case '/': result = num2 != 0 ? num1 / num2 : 0; break;
default: result = 0; break;
}
printf("Result: %d\n", result);
} else {
printf("Invalid input\n");
}
}
int main() {
// Create the FIFO (named pipe)
if (mkfifo(PIPE_NAME, 0666) == -1 && errno != EEXIST) {
perror("mkfifo");
return 1;
}printf("Server is waiting for client requests...\n");
char buffer[100];
int fd = open(PIPE_NAME, O_RDONLY);
if (fd == -1) {
perror("open");
return 1;
}
while (1) {
memset(buffer, 0, sizeof(buffer));
int bytes = read(fd, buffer, sizeof(buffer) - 1);
if (bytes <= 0) break;
process_request(buffer);
}
close(fd);
return 0;
}
