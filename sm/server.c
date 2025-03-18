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
// Create shared memory and map it
int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
ftruncate(shm_fd, PRICE_SIZE);
char *price_in_memory = mmap(NULL, PRICE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
shm_fd, 0);
// Create semaphore for synchronization
sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);// Simulate updating Google stock price
while (1) {
float price = 2500 + rand() % 100; // Simulated stock price (Google stock)
snprintf(price_in_memory, PRICE_SIZE, "Google Stock: $%.2f", price);
// Synchronize access to shared memory
sem_wait(sem);
printf("Server: Updated stock price: $%.2f\n", price);
sem_post(sem);
sleep(5); // Update every 5 seconds
}
// Cleanup
sem_close(sem);
munmap(price_in_memory, PRICE_SIZE);
close(shm_fd);
return 0;
}
