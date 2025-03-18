#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
FILE *write_pipe, *read_pipe;
char write_msg[] = "Hello from parent to child via pipe using popen! Type your message.";
char read_msg[100];

write_pipe = popen("cat", "w"); 
if (write_pipe == NULL) {
perror("popen for write failed");
return 1;
}
fprintf(write_pipe, "%s\n", write_msg);
pclose(write_pipe);
read_pipe = popen("cat", "r"); 
if (read_pipe == NULL) {
perror("popen for read failed");
return 1;}
// Read the message from the pipe
if (fgets(read_msg, sizeof(read_msg), read_pipe) != NULL) {
printf("Parent process received message: '%s'", read_msg);
}
pclose(read_pipe); // Close the reading end
return 0;
}
