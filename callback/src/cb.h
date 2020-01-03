#ifndef CB_H_INCLUDED
#define CB_H_INCLUDED

typedef enum JuCB_ACT_TYPE {
	JuCB_ACT_WALK = 0,
	JuCB_ACT_RUN,
	JuCB_ACT_ATTACK
} JuCB_ACT_TYPE;

typedef enum JuCB_STA_TYPE {
	JuCB_STA_SLEEP = 0,
	JuCB_STA_AWAKE,
	JuCB_STA_HUNGRY
} JuCB_STA_TYPE;

typedef struct
{
	void (*JuCB_action_cb)(void* pvPrivate, JuCB_ACT_TYPE event);
	void (*JuCB_state_cb)(void* pvPrivate, JuCB_STA_TYPE event, char* msg);
} JuCB_CallBack_T;

typedef struct JuCB JuCB;
struct JuCB
{
	JuCB_CallBack_T cb;

	void (*action)(JuCB* obj);
	void (*state)(JuCB* obj);
	void (*register_cb)(JuCB* obj, JuCB_CallBack_T* cb);
	void (*destroy)(JuCB* obj);
};

static inline void JuCB_action(JuCB* obj)
{
	obj->action(obj);
}

static inline void JuCB_state(JuCB* obj)
{
	obj->state(obj);
}

static inline void JuCB_register_cb(JuCB* obj, JuCB_CallBack_T* cb)
{
	obj->register_cb(obj,cb);
}

static inline void JuCB_destroy(JuCB* obj)
{
	obj->destroy(obj);
}

JuCB* JuCB_init();


#endif

