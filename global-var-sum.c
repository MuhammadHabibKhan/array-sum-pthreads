#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h> 

int data[100];
int dataLength = sizeof(data)/sizeof(data[0]);

int sum = 0;

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void generateData()
{
    for (int i = 0; i < dataLength; i++) { data[i] = i+1; }
}

void *summation(void *arg)
{
    int local_sum = 0;
    int *arr = (int *) arg; // telling compiler to deal the array in args as int type
    int start = arr[0];
    int workLoad = arr[1];

    for (int i = 0; i < workLoad; i++)
    {
        local_sum += *(data + start + i);
    }

    pthread_mutex_lock(&mut);
    sum += local_sum; // critical section
    pthread_mutex_unlock(&mut);
    
    printf("Sum from %d to %d: %d \n", start + 1, start + workLoad, sum);
    free(arg); // free memory where it is assigned 
}

void assignWorkload(int threads)
{
    int extraWorkLoad = 0;
    int workLoad = dataLength / threads;

    int *threadEWL = malloc(threads * sizeof(int));
    pthread_t *threadArray = malloc(threads * sizeof(pthread_t));

    if ( dataLength % threads != 0)
    {
        extraWorkLoad = dataLength % threads;
        printf("EWL: %d \n", extraWorkLoad);
    }

    int index = 0;

    while (extraWorkLoad != 0)
    {
        threadEWL[index % threads] += 1;
        extraWorkLoad -= 1;
        index += 1;
    }

    for (int i = 0; i < threads; i++)
    {
        int *args = malloc(2 * sizeof(int));

        args[0] = i * workLoad;
        args[1] = workLoad + threadEWL[i];

        pthread_t thread;
        threadArray[i] = thread;
        pthread_create(&threadArray[i], NULL, summation, (void *)args);
    }

    for (int j = 0; j < threads; j++)
    {
        pthread_join(threadArray[j], NULL);
    }

    printf("Total Sum: %d \n", sum);
    free(threadArray);
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
