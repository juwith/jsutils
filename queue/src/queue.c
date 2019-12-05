#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void _queue_enque(Queue* queue, void* item)
{
	printf("push\n");
}

void* _queue_deque(Queue* queue)
{
	printf("pop\n");
}

void _queue_destroy(Queue* queue)
{
	free(queue);
	queue = NULL;
}

Queue* Queue_init()
{
	static struct QueueFuncTable functable = {
		_queue_enque,
		_queue_deque,
		_queue_destroy
	};

	Queue *queue = (Queue *)calloc(1, sizeof(Queue));
	queue->functable = &functable;
	return queue;
}

