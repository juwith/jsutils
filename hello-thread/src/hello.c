#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* threadfunc1(void *data)
{
	int indata = *(int*)data;
	for(int i=0; i<10; i++)
	{
		printf("hello thread 1, input data : %d\n",indata);
		usleep(1000);
	}
}

void* threadfunc2(void *data)
{
	int indata = *(int*)data;
	for(int i=0; i<15; i++)
	{
		printf("hello thread 2, input data : %d\n",indata);
		usleep(700);
	}
}

int main()
{
	pthread_t p_thread[2];
	int status;
	int data[2] = {1,2};

	pthread_create(&p_thread[0], NULL, threadfunc1, (void *)&data[0]);
	pthread_create(&p_thread[1], NULL, threadfunc2, (void *)&data[1]);

	pthread_join(p_thread[0], (void **)&status);
	printf("thread exit 1\n");
	
	pthread_join(p_thread[1], (void **)&status);
	printf("thread exit 2\n");
		

	return 0;
}
