#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(){
int pipefd[2];
char write_msg[]="Hello from pipe!";
char read_msg[20];
if(pipe(pipefd)==-1){
perror("pipe");
return 1;
}
if(fork()==0){
close(pipefd[0]);
write(pipefd[1], write_msg, strlen(write_msg) + 1);
close(pipefd[1]);
}else{
close(pipefd[1]);
read(pipefd[0], read_msg, sizeof(read_msg));
printf("Received:%s\n", read_msg);
close(pipefd[0]);
}
return 0;
}
