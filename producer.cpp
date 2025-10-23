//Caleb Stanberry

#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

int main() {
    const char *name = "/sharedMemory";
    const char *fillSem = "/fill";
    const char *availSem = "/avail";
    const char *mutexSem = "/mutex";

    const int SIZE = 2; //Table size
    const int LOOP = 6; //Number of loops

    sem_t *fill, *ready, *mutex;
    int shared_memory_fd;
    int *buffer;

    // Shared memory to access the table
    shared_memory_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shared_memory_fd, SIZE * sizeof(int));

    buffer = (int *)mmap(0, SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);
    
    // Handling error for shared mem
    if(buffer == MAP_FAILED) {
        return 1;
    }

    // Init shared memory
    for (int i = 0; i < SIZE; i++) buffer[i] = 0;

    // Set semaphores
    fill = sem_open(fillSem, O_CREAT, 0666, 0);
    ready = sem_open(availSem, O_CREAT, 0666, SIZE);
    mutex = sem_open(mutexSem, O_CREAT, 0666, 1);

    std::cout << "Producer start\n";

    for (int i = 0; i < LOOP; i++) {
        sem_wait(ready);
        sem_wait(mutex);

        // Finds empty slot and fills it with item
        for (int slot = 0; slot < SIZE; slot++) {
            if (buffer[slot] == 0) {
                buffer[slot] = 1;
                std::cout << "Produced item in slot " << slot << std::endl;
                break;
            }
        }

        sem_post(mutex);
        sem_post(fill);

        sleep(1);
    }
    std::cout << "Producer done\n";

    // Cleanup (with unlink producer)
    sem_close(fill);
    sem_close(mutex);
    sem_close(ready);


    sem_unlink(fillSem);
    sem_unlink(mutexSem);
    sem_unlink(availSem);

    munmap(buffer, SIZE * sizeof(int));
    close(shared_memory_fd);

    shm_unlink(name);

    return 0;
}
