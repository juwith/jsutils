#include <stdio.h>
#include <unistd.h> //sleep
#include <pthread.h>

#include <stdlib.h> //rand

typedef struct tHandle tHandle;

struct tHandle
{
	int value;
	pthread_mutex_t mutex;
};

void* threadfunc1(void *data)
{
	tHandle* phandle = (tHandle*)data;
	for(int i=0; i<1000; i++)
	{
		pthread_mutex_lock(&phandle->mutex);

		phandle->value = 1;
		rand(); //do something.
		if(phandle->value != 1)
			printf("race condition in thread 1!!!!\n"); //if there is no mutex it is occured.

		pthread_mutex_unlock(&phandle->mutex);
		usleep(1000);
	}

	pthread_exit(NULL); //set return val if it is
}

void* threadfunc2(void *data)
{
	tHandle* phandle = (tHandle*)data;
	for(int i=0; i<1000; i++)
	{
		pthread_mutex_lock(&phandle->mutex);
		phandle->value = 2;
		rand(); //do something.
		if(phandle->value != 2)
			printf("race condition in thread 2!!!!\n"); //if there is no mutex it is occured.

		pthread_mutex_unlock(&phandle->mutex);
		usleep(1000);
	}

	pthread_exit(NULL); //set return val if it is
}

int main()
{
	pthread_t p_thread[2];
	int status;
	tHandle handle;
	handle.value = 0;
	pthread_mutex_init(&handle.mutex, NULL);
	pthread_create(&p_thread[0], NULL, threadfunc1, (void *)&handle);
	pthread_create(&p_thread[1], NULL, threadfunc2, (void *)&handle);

	pthread_join(p_thread[0], (void **)&status);
	printf("thread exit 1\n");
	pthread_join(p_thread[1], (void **)&status);
	printf("thread exit 2\n");

	pthread_mutex_destroy(&handle.mutex);
	return 0;
}
