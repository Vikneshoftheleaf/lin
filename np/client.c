#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define PIPE_NAME "/tmp/calc_fifo"
int main() {
int fd = open(PIPE_NAME, O_WRONLY);
if (fd == -1) {
perror("open");
return 1;
}
char request[100];
printf("Enter a calculation (e.g., 3+4): ");
fgets(request, sizeof(request), stdin);
request[strcspn(request, "\n")] = 0; // Remove newline character
write(fd, request, strlen(request) + 1); // Send request to the server
close(fd);
return 0;
}
