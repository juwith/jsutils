#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void _queue_enque(Queue* queue, void* item)
{
	qData* newQData = (qData*)malloc(sizeof(qData));
	if(queue->front == NULL)
	{
		queue->front = newQData;
		queue->rear = queue->front;
	}
	else
	{
		queue->rear->next = newQData;
		queue->rear = queue->rear->next;
	}
	newQData->next = NULL;
	newQData->item = item;
	queue->nItem++;
}

void* _queue_deque(Queue* queue)
{
	if(queue->front == NULL)
		return NULL;

	void* item = queue->front->item;
	qData* qnext = queue->front->next;
	free(queue->front);
	queue->front = qnext;

	queue->nItem--;
	return item;
}

int _queue_get_itemNum(Queue* queue)
{
	if(queue == NULL)
		return -1;

	return queue->nItem;
}

void _queue_flush(Queue* queue)
{
	while(queue->front != NULL)
	{
		void* item = _queue_deque(queue);
		if(item) free(item);
	}
}

void _queue_destroy(Queue* queue)
{
	_queue_flush(queue);
	free(queue);
	queue = NULL;
}

Queue* Queue_init()
{
	static struct QueueFuncTable functable = {
		_queue_enque,
		_queue_deque,
		_queue_get_itemNum,
		_queue_flush,
		_queue_destroy
	};

	Queue *queue = (Queue *)calloc(1, sizeof(Queue));
	queue->functable = &functable;
	return queue;
}

