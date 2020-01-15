#include <stdio.h>
#include <unistd.h> //sleep
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

#include "message.h"

void* _message_thread(void* msg)
{
	Message* pMsg = (Message*)msg;
	pMsg->threadAlive = true;
	Queue* pQ = pMsg->queue;
	void* item = NULL;
	while(pMsg->threadAlive)
	{
		pthread_mutex_lock(&pMsg->msgMtx);

		item = Queue_Dequeue(pQ);
		if(item != NULL)
		{
			pMsg->cb.msg_process(pMsg,item);
		}
		pthread_mutex_unlock(&pMsg->msgMtx);

		usleep(pMsg->msgThrIntv);
	}
	pthread_exit(NULL); //set return val if it is
}

void _message_send(Message* msg, void* item)
{
	pthread_mutex_lock(&msg->msgMtx);
	Queue* q = msg->queue;
	Queue_Enqueue(q,item);
	pthread_mutex_unlock(&msg->msgMtx);
}

void _message_flush(Message* msg)
{
	pthread_mutex_lock(&msg->msgMtx);
	Queue_Flush(msg->queue);
	pthread_mutex_unlock(&msg->msgMtx);
}

int _message_get_count(Message* msg)
{
	return Queue_Get_ItemNum(msg->queue);
}

void _message_destroy(Message* msg)
{
	int status;
	msg->threadAlive = false;
	pthread_join(msg->msgThread, (void **)&status);
	pthread_mutex_destroy(&msg->msgMtx);
	Queue_destroy(msg->queue);
	msg->queue = NULL;

	free(msg);
	msg = NULL;
}

Message* Message_init(MSG_CallBack_T* cb, uint32_t msgInterval)
{
	Message *msg = (Message *)calloc(1, sizeof(Message));

	msg->threadAlive = false;
	msg->queue = Queue_init();

	msg->cb.msg_process = cb->msg_process;

	msg->send = _message_send;
	msg->flush = _message_flush;
	msg->get_count = _message_get_count;
	msg->destroy = _message_destroy;

	msg->msgThrIntv = msgInterval;
	pthread_mutex_init(&msg->msgMtx, NULL);
	pthread_create(&msg->msgThread, NULL, _message_thread, msg);

	return msg;
}

