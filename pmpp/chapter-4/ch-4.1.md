### QUESTION

A student mentioned that he was able to multiply two 1024x1024
matrices using a tiled matrix multiplication code with 1024 thread
blocks on the G80. He further mentioned that each thread in a thread
block calculates one element of the result matrix. What would be your
reaction and why?


### Answer
The maximum Number of threads/block in G80 GPU is 512 threads/Block.
If we multiply two 1024x1024 matrix the result is also a 1024x1024 matrix and it is mentioned that 1024 blocks are used to perform this matmul.
However,

$$\frac{1024{\times}1024}{1024} = 1024{\text{ threads/block}} > 512{\text{ threads/block}}$$

Thus This is not possible to implement on a G80 GPU.