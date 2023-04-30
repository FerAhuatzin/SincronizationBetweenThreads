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

pthread_mutex_t mutex; // Mutex para controlar la escritura en la salida estándar
pthread_cond_t helloReady;
int hello_written = 0;

void* hello(void* arg) 
{
    // Aquí va el código para escribir "Hola " y tratar la región crítica
    pthread_mutex_lock(&mutex);
    printf("Hello ");
    hello_written=1;
    pthread_cond_signal(&helloReady);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void* world(void* arg) 
{
    pthread_mutex_lock(&mutex);

    while( hello_written == 0 )
    {
        // Aquí va el código para la variable de condición
        pthread_cond_wait(&helloReady,&mutex);
    }

    // Aquí va el código para escribir "mundo!\n" y liberar la región crítica
    printf("World\n");
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread_1, thread_2;

    // Aquí va el código para crear el mutex, las variables de condición y los hilos
	pthread_mutex_init(&mutex,0);
	pthread_create(&thread_1,NULL,hello,NULL);
    pthread_create(&thread_2,NULL,world,NULL);
    // Aquí esperas a los hilos
	pthread_join(thread_1,NULL);
    pthread_join(thread_2,NULL);
    // Aquí destruyes al mutex y las variables de condición
    pthread_mutex_destroy(&mutex);
    return 0;
}
