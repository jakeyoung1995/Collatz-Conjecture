# Collatz-Conjecture
This project contains two programs: Collatz-Producer.c and Collatz-Consumer.c

## Collatz-Producer
This program will write the contents of the sequence to the shared-memory object. 
It will do this by:
1.) Performing error checking to ensure that the input is valid.
2.) Establishing the shared-memory object.
3.) Writing the contents of the shared memory.

## Collatz-Consumer
This program will output the sequence when the producer completes.
It will do this by: 
1.) Opening the shared-memory object.
2.) Outputting the contents of the shared memory.
3.) Removing the shared-memory object.
