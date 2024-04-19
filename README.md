# Sum of Array using Multi-threading (pthreads)
- A simple program utilizing multi-threading to calculate the sum of an array using 2 techniques. 
- This program is beginner-friendly and should be implemented by folks starting to work with multi-threading to get the hang of it.

## Methods:

### 1. Using local variable
- This method allows for faster calculations since each thread does not have to wait for the memory resource

### 2. Using global shared variable
- Implementing using a global variable requires the use of mutex or similar resource management techniques on the critical section of the code to achieve concurrency and avoid bad reads and potential deadlocks.
- Since each thread has to wait for the resource, the compute time naturally goes up.

## Workload Division:
- The workload is divided equally among the available threads.
- If any workload remains after maximum equal assignment to each thread, the extra workload is assigned to the threads in a round-robin fashion. 

## Pre-Requisites:
- pthreads library.
- Use the pthread flag when compiling the code.
- See Guide.txt regarding running pthreads library in Windows.
