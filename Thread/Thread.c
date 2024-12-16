/*
    Detail:
    The program creates 10 threads, which are 9 Readers and 1 Writer
    The writer is placed as main priority, meaning if a reader is executing
    the reader must finish the program and immediatly hands the lock to writer.
    There also exist a critial section in which all thread must access carefully.

    This code is meant to showcase the understanding of Race Condition and Deadlocks
    this of course uses spinlocks, and Semaphores mutex lock to prevent these type of scenario.
*/


#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_mutex_t db;
int rc = 0; // Critial Section
int wait = 0;

void *reader(void *i)
{
    pthread_mutex_lock(&mutex);          //get exclusive access to rc

    while(wait > 0)                     // If writer set the flag! all reader must wait inside the Spinlock
    {
        pthread_mutex_unlock(&mutex);  // Avoids any deadlock
        pthread_mutex_lock(&mutex);   // Relock the mutex when no writers are waiting
    }

    rc = rc + 1;                            //one more reader now
    
    if(rc == 1)
        pthread_mutex_lock(&db);            //if this is the a reader...
    
    pthread_mutex_unlock(&mutex);         //release exclusive access to rc
                                         //”i” is a thread that is [1..10] passed from main
    printf("Reader %d in critical section\n", *((int *)i));
    pthread_mutex_lock(&mutex);                               //get exclusive access to rc
    rc = rc - 1;                                             //one reader fewer now
    
    if(rc == 0)
        pthread_mutex_unlock(&db);                  //if the last reader ..
        
    pthread_mutex_unlock(&mutex);                   //release exclusive access to rc
    printf("Reader %d in non-critical section\n",*((int *)i));

    return NULL;
}

void *writer(void *i)
{
    printf(" =Writer %d tries to enter the critical section= \n", *((int *)i));

    pthread_mutex_lock(&mutex);     // Lock all threads to indicate the wait
    wait++;
    pthread_mutex_unlock(&mutex); // they should be in a waiting loop

    pthread_mutex_lock(&db);
    printf(" =Writer %d is in critical region= \n", *((int *)i));
    pthread_mutex_unlock(&db);
    printf(" =Writer %d is in non-critical region= \n", *((int *)i));

    pthread_mutex_lock(&mutex);     // Lock all threads to indicate the wait
    wait--;
    pthread_mutex_unlock(&mutex); // all threads should be running now

    return NULL;
}

int main()
{
    int a;
    pthread_t p[10];

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&db, NULL);

    int b[10] = {1,2,3,4,5,6,7,8,9,10};

    for (a = 0; a < 10; a++)
    {
        if(a == 1) // Must be the 2nd thread
            pthread_create(&p[a], NULL, writer, &b[a]); // 1 Writer
        else
            pthread_create(&p[a], NULL, reader, &b[a]); // 9 Reader
    }

    printf("\n\n====================\n\n");

    for (a = 0; a < 10; a++)
    {
        pthread_join(p[a], NULL);
        printf("Number of thread Join(finished): %d \n", a+1);
    }
    
    return 0;
}