/*
The consumer process outputs the sequence when the producer completes.

1.) Open the shared-memory object.
2.) Output the contents of the shared memory.
3.) Remove the shared-memory object.

UNIX Compiler: gcc Collatz-Consumer.c -o Collatz-Consumer -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, const char **argv){

    const char *Obj = "Shm"; // Define name of the shared memory

    int shm_fd = shm_open(Obj, O_RDONLY, 0666); // Open shared memory for file reading

    // Memory Check
    if(shm_fd == -1) {
        printf("Shared Memory failed\n");
        exit(-1);
    }

    size_t size = 4096; // Size of shared memory object

    int *ptr = mmap(0, size, PROT_READ, MAP_SHARED, shm_fd, 0); // Mapping
    
    // Map Check
    if(ptr == MAP_FAILED) {
        printf("Map Failed\n");
        exit(-1);
    }

    printf("Consumer: The output sequence is: "); // Update the user

    // Print the sequence to the user
    while(*ptr != 0){
        printf("%d, ", *ptr);
        ++ptr;
    }

    // Remove the shared memory object
    if(shm_unlink(Obj) == -1) {
        printf("Error removing %s\n", Obj);
        exit(-1);
    }

    return 0;
}