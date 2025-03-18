#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
void scan_directory(const char *dir_path) {
// Open the directory using opendir() system call
DIR *dir = opendir(dir_path);
if (dir == NULL) {
perror("Failed to open directory");
return;
}
struct dirent *entry;
// Read each entry in the directory using readdir()
while ((entry = readdir(dir)) != NULL) {
// Print the name of each file/directory
printf("%s\n", entry->d_name);
}
// Close the directory using closedir()
closedir(dir);
}
int main(int argc, char *argv[]) {
if (argc != 2) {
fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
exit(EXIT_FAILURE);
}
// Call the function to scan the directory
scan_directory(argv[1]);
return 0;
}
