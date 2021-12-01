/* 
The producer process writes the contents of the sequence to the shared-memory object

1.) Perform error checking to ensure that the input is valid.
2.) Establish the shared-memory object.
3.) Writes the contents of the shared memory.

UNIX Compiler: gcc Collatz-Producer.c -o Collatz-Producer -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>


static int computeCollatz(int num){
    if(num % 2 == 0){
        return num / 2;
    } else {
        return 3 * num + 1;
    }
}

int main(int argc, const char **argv) {

    int term = atoi(argv[1]); // Input as initial term
    const char *Obj = "Shm"; // Define name of the shared memory

    int shm_fd = shm_open(Obj, O_CREAT | O_RDWR, 0666); // Open shared memory for file editing

    size_t size = 4096; // The size of the Shared Memory object

    ftruncate(shm_fd, size); // Size configuration

    int *ptr = mmap(0, size, PROT_WRITE, MAP_SHARED, shm_fd, 0); // Shared-memory object mapping

    if(ptr == MAP_FAILED) {
        printf("Map failed\n");
        return -1;
    }

    // Compute Collatz conjecture and write it to the shared memory
    ptr[0] = term;

    size_t sequence_length = 1;
    
    do{
        term = computeCollatz(term);
        ptr[sequence_length] = term;
        ++sequence_length;
    }while(sequence_length != 100 && term != 1);

    ptr[sequence_length] = 0;

    // Print update to the user
    printf("Producer: Writing the sequence to the shared-memory object is done!\n");

    // Close shared memory
    close(shm_fd);
    return 0;
}