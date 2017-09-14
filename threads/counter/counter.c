#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "counter.h"

#define THREAD_COUNT 1000


static void *thread_incr(void *arg)
{
        int *counter = (int *)arg;

        *counter = *counter + 1000;

        return (void *)*counter;
}

int main(void)
{
        pthread_t tid[THREAD_COUNT];
        int i;
        int counter = 0;

        for (i = 0; i < THREAD_COUNT; i++) {
                void *ret;

                if (pthread_create(&tid[i], NULL, &thread_incr, &counter) != 0) {
                        fprintf(stderr, "Error creating thread\n");
                        exit(EXIT_FAILURE);
                }

                if (pthread_join(tid[i], &ret) != 0) {
                        fprintf(stderr, "Error joining thread to main\n");
                }

                counter = (int) ret;
        }

        printf("Counter value: %d\n", counter);
        exit(EXIT_SUCCESS);
}
