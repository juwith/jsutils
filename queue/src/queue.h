#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct qData qData;

struct qData
{
	qData* next;
	void* item;
};

typedef struct Queue
{
	qData* front;
	qData* rear;
	int nItem;
	struct QueueFuncTable *functable;
} Queue;

struct QueueFuncTable
{
	void (*enqueue)(Queue* queue, void* item);
	void* (*dequeue)(Queue* queue);
	int (*get_itemNum)(Queue* queue);
	void (*flush)(Queue* queue);
	void (*destroy)(Queue* queue);
};

static inline void Queue_Enqueue(Queue *obj,void* item)
{
	obj->functable->enqueue(obj,item);
}

static inline void* Queue_Dequeue(Queue *obj)
{
	return obj->functable->dequeue(obj);
}

static inline int Queue_Get_ItemNum(Queue *obj)
{
	return obj->functable->get_itemNum(obj);
}

static inline void Queue_Flush(Queue *obj)
{
	return obj->functable->flush(obj);
}

static inline void Queue_destroy(Queue *obj)
{
	obj->functable->destroy(obj);
}

Queue* Queue_init();


#endif
