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
    shared_memory_fd = shm_open(name, O_RDWR, 0666);
    buffer = (int *)mmap(0, SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shared_memory_fd, 0);

    //Handling error shared mem
    if(buffer == MAP_FAILED) { 
        return 1;
    }

    // Open semaphores
    int attempts = 0; // Attempts counter to try opening semaphore
    while((fill = sem_open(fillSem, 0)) == SEM_FAILED && attempts++ < 5) {
        sleep(1);
    }
    ready = sem_open(availSem, 0);
    mutex = sem_open(mutexSem, 0);


    if (fill == SEM_FAILED || ready == SEM_FAILED || mutex == SEM_FAILED) {
        std::cerr << "Consumer failed to open semaphores\n";
        return 1;
    }

    std::cout << "Consumer start\n";

    for (int i = 0; i < LOOP; i++) {
        sem_wait(fill);
        sem_wait(mutex);

        // Finds slot with item and consumes it
        for (int slot = 0; slot < SIZE; slot++) {
            if (buffer[slot] == 1) {
                buffer[slot] = 0;
                std::cout << "Consumed item from slot " << slot << std::endl;
                break;
            }
        }

        sem_post(mutex);
        sem_post(ready);

        sleep(3);
    }
    std::cout << "Consumer done\n";

    // Cleanup (without unlink)
    sem_close(fill);
    sem_close(mutex);
    sem_close(ready);

    munmap(buffer, SIZE * sizeof(int));
    close(shared_memory_fd);

    return 0;
}
