#include <stdio.h>
#include <stdlib.h>
#include "cb.h"

void _jucb_action(JuCB* obj)
{
	if(!obj->cb.JuCB_action_cb)
	{
		printf("you need to register action cb!\n");
		return;
	}

	//printf("action callback\n");
	obj->cb.JuCB_action_cb(
		obj,
		JuCB_ACT_RUN);
}

void _jucb_state(JuCB* obj)
{
	if(!obj->cb.JuCB_state_cb)
	{
		printf("you need to register state cb!\n");
		return;
	}

	char* msg = "I am hungry";

	//printf("state callback\n");
	obj->cb.JuCB_state_cb(
		obj,
		JuCB_STA_HUNGRY,
		msg);
}

void _jucb_register_cb(JuCB* obj, JuCB_CallBack_T* cb)
{
	obj->cb.JuCB_action_cb = cb->JuCB_action_cb;
	obj->cb.JuCB_state_cb = cb->JuCB_state_cb;
	//printf("register cb\n");
}

void _jucb_destroy(JuCB* obj)
{
	free(obj);
	obj = NULL;
}

JuCB* JuCB_init()
{
	JuCB *obj = (JuCB*)calloc(1, sizeof(JuCB));

	//add child
	obj->action = _jucb_action;
	obj->state = _jucb_state;
	obj->register_cb = _jucb_register_cb;
	obj->destroy = _jucb_destroy;

	return obj;
}

