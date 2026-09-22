### Question
If the code (Ex. 4.2) does not execute correctly for all BLOCK_SIZE values,
suggest a fix to the code to make it work for all BLOCK_SIZE values.

### Answer:
We know that there exist a race condition between two threads accessing the shared memory thus a syncronization mechanism between the two threads is needed.

This can be achieved using __syncthreads() intrinsic;