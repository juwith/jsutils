#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct Queue
{
	struct QueueFuncTable *functable;
} Queue;

struct QueueFuncTable
{
	void (*enqueue)(Queue* queue, void* item);
	void* (*dequeue)(Queue* queue);
	void (*destroy)(Queue* queue);
};

#define Queue_Enqueue(obj,item) \
	((Queue*)obj)->functable->enqueue(obj,item)

#define Queue_Dequeue(obj) \
	((Queue*)obj)->functable->dequeue(obj)

#define Queue_destroy(obj) \
	((Queue*)obj)->functable->destroy(obj)

Queue* Queue_init();


#endif
