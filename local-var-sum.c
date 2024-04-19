#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int data[100];
int dataLength = sizeof(data)/sizeof(data[0]);

void generateData()
{
    for (int i = 0; i < dataLength; i++) { data[i] = i+1; }
}

void *summation(void *arg)
{
    int *sum = malloc(sizeof(int));
    int *arr = (int *) arg; // telling compiler to deal the array in args as int type
    int start = arr[0];
    int workLoad = arr[1];

    for (int i = 0; i < workLoad; i++)
    {
        // printf("Sum of: %d \n", *(data + start + i));
        *sum += *(data + start + i);
    }
    printf("Sum from %d to %d: %d \n", start+1, start+workLoad, *sum);
    free(arr);
    return (void *) sum;
}

void assignWorkload(int threads)
{
    int totalSum = 0;
    int extraWorkLoad = 0;
    int workLoad = dataLength / threads;
    int *results = malloc(threads * sizeof(int));
    int *threadEWL = malloc(threads * sizeof(int));
    pthread_t *threadArray = malloc(threads * sizeof(pthread_t));

    if ( dataLength % threads != 0)
    {
        extraWorkLoad = dataLength % threads;
        printf("EWL: %d \n", extraWorkLoad);
    }

    // Divide the extra workload between threads
    int index = 0;

    while (extraWorkLoad != 0)
    {
        threadEWL[index % threads] += 1;
        extraWorkLoad -= 1;
        index += 1;
    }

    for (int i = 0; i < threads; i++)
    {
        // int args[2]; 
        // holds starting index and workload for each thread
        // using dynamic array here as re-creation of same array on stack may occur on the same
        // memory area causing race conditions and bad read | Output was bad also (checked)
        // Cannot declare it outside loop or else race condition between threads for the values.

        int *args = malloc(2 * sizeof(int));
        args[0] = i * workLoad;

        args[1] = workLoad + threadEWL[i];

        pthread_t thread;
        threadArray[i] = thread;
        pthread_create(&threadArray[i], NULL, summation, (void *)args);
    }
    for (int j = 0; j < threads; j++)
    {
        void *result;
        pthread_join(threadArray[j], (void **) &result);
        results[j] = *(int *)result;
        totalSum += results[j];
        printf("Sum of thread %d: %d \n", j + 1, results[j]);
        free(result); // Free the memory allocated in summation function
    }
    printf("Total Sum: %d \n", totalSum);

    free(threadArray);
    free(results);
}

int main (int argc, char *argv[])
{
    clock_t begin = clock();

    generateData();
    assignWorkload(4);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Time Spent: %f \n ", time_spent);

    return 0;
}
