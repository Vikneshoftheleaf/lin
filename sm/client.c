#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#define SHM_NAME "/google_stock"
#define SEM_NAME "/sem_stock"
#define PRICE_SIZE 50
int main() {
// Open shared memory
int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
char *price_in_memory = mmap(NULL, PRICE_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
// Open semaphore for synchronization
sem_t *sem = sem_open(SEM_NAME, 0);
while (1) {
// Synchronize access to shared memory
sem_wait(sem);
printf("Client: Latest stock price: %s\n", price_in_memory);
sem_post(sem);
sleep(2); // Display updated stock price every 2 seconds
}// Cleanup
sem_close(sem);
munmap(price_in_memory, PRICE_SIZE);
close(shm_fd);
return 0;
}
