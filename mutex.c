#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h>


pthread_mutex_t mutex; 
int count = 0; 

void* hilo(void* arg) 
{
    pthread_mutex_lock(&mutex);
    count++;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() 
{
    pthread_t t1, t2, t3, t4, t5;
    // Aquí va el código para crear el mutex
    pthread_mutex_init(&mutex,0);
    
    // Aquí va el código para crear los hilos
    pthread_create(&t1,NULL,hilo,NULL);
    pthread_create(&t2,NULL,hilo,NULL);
    pthread_create(&t3,NULL,hilo,NULL);
    pthread_create(&t4,NULL,hilo,NULL);
    pthread_create(&t5,NULL,hilo,NULL);
    // Aquí va el código para esperar a que los hilos terminen
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
    // Aquí va el código para imprimir el valor final del contador
    printf("El valor final del contador es: %d\n", count);
    
    // Aquí va el código para destruir el mutex
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
