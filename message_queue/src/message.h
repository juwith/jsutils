#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdbool.h>
#include <stdint.h>

#include "queue.h"

typedef struct Message Message;

typedef struct
{
	void (*msg_process)(void* pvPrivate, void* item);
} MSG_CallBack_T;

struct Message
{
	//private
	Queue* queue;
	MSG_CallBack_T cb;
	pthread_t msgThread;
	pthread_mutex_t msgMtx;
	uint32_t msgThrIntv;
	bool threadAlive;
	
	//public
	void (*send)(struct Message* msg, void* item);
	void (*flush)(struct Message* msg);
	int (*get_count)(struct Message* msg);
	void (*destroy)(struct Message* msg);
};

static inline void Message_Send(Message *msg, void* item)
{
	msg->send(msg,item);
}

static inline void Message_Flush(Message *msg)
{
	msg->flush(msg);
}

static inline int Message_GetCount(Message *msg)
{
	return msg->get_count(msg);
}

static inline void Message_destroy(Message *msg)
{
	msg->destroy(msg);
}

Message* Message_init(MSG_CallBack_T* cb, uint32_t msgInterval);


#endif

