#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep
#include <pthread.h>
#include <string.h>

#include "message.h"

void* ThrSend(void *pvPrivate)
{
	Message* msg = (Message*)pvPrivate;
	for(int i=0; i<100; i++)
	{
		char* item = malloc(10);
		sprintf(item, "item %d\n", i+1);
		Message_Send(msg,item);
		usleep(1000*5);
	}
	pthread_exit(NULL); //set return val if it is
}

void* ThrFlush(void *pvPrivate)
{
	Message* msg = (Message*)pvPrivate;
	for(int i=0; i<3; i++)
	{
		usleep(1000*300);
		printf("flush!! before count : %d \n",Message_GetCount(msg));
		Message_Flush(msg);
		printf("flush!! after count : %d \n",Message_GetCount(msg));
	}
	pthread_exit(NULL); //set return val if it is
}

static void _msgcb_process(void* pvPrivate, void* item)
{
	Message* msg = (Message*)pvPrivate;
	//use and free
	printf("do someting %s",(char*)item);
	
	free(item);
	item = NULL;
}

int main()
{
	MSG_CallBack_T cb;
	cb.msg_process = _msgcb_process;
	Message* msg = Message_init(&cb,1000*10);

	pthread_t pthSend;
	pthread_t pthFlush;
	pthread_create(&pthSend, NULL, ThrSend, msg);
	pthread_create(&pthFlush, NULL, ThrFlush, msg);

	int status;
	pthread_join(pthSend, (void **)&status);
	pthread_join(pthFlush, (void **)&status);

	Message_destroy(msg);
	printf("destroy msg\n");

	return 0;
}
