#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep
#include <pthread.h>

#include "queue.h"

typedef struct tHandle tHandle;

struct tHandle
{
	Queue *queue;
	pthread_mutex_t mutex;
};

void* thrEnqueue(void *data)
{
	tHandle* pHandle = (tHandle*)data;
	Queue *queue = pHandle->queue;
	for(int i=0; i<1000; i++)
	{
		pthread_mutex_lock(&pHandle->mutex);

		int* item = (int*)malloc(sizeof(int));
		Queue_Enqueue(queue,item);
		printf("queue : %d\n",Queue_Get_ItemNum(queue));

		pthread_mutex_unlock(&pHandle->mutex);
		int time = rand()%100;
		usleep(time);
	}
	pthread_exit(NULL); //set return val if it is
}

void* thrDequeue(void *data)
{
	tHandle* pHandle = (tHandle*)data;
	Queue *queue = pHandle->queue;
	for(int i=0; i<1000; i++)
	{
		pthread_mutex_lock(&pHandle->mutex);

		if(Queue_Get_ItemNum(queue) > 0)
		{
			int* item = Queue_Dequeue(queue);
			if(item) free(item);
			printf("dequeue : %d\n",Queue_Get_ItemNum(queue));
		}

		pthread_mutex_unlock(&pHandle->mutex);
		int time = rand()%100;
		usleep(time);
	}
	pthread_exit(NULL); //set return val if it is
}

int main()
{
	int data = 1;

	tHandle handle;
	pthread_mutex_init(&handle.mutex, NULL);
	handle.queue = Queue_init();

	pthread_t p_thread[2] = {NULL,};
	pthread_create(&p_thread[0], NULL, thrEnqueue, (void *)&handle);
	pthread_create(&p_thread[1], NULL, thrDequeue, (void *)&handle);
	

	pthread_join(p_thread[0], NULL);
	printf("thread exit 1\n");
	pthread_join(p_thread[1], NULL);
	printf("thread exit 2\n");

	Queue_destroy(handle.queue);
	pthread_mutex_destroy(&handle.mutex);
	return 0;
}
