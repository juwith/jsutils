#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "humman.h"

void _humman_set_name(Human *obj,char* name)
{
	strcpy(obj->name,name);
}

char* _humman_get_name(Human *obj)
{
	return obj->name;
}

void _humman_print_info(Human *obj)
{
	printf("human name %s age %d alive %d\n",obj->name,obj->age,obj->alive);
}

void _humman_action(Human* obj)
{
	printf("base action from humman class\n");
}

void _humman_set_alive(Human* obj, bool alive)
{
	obj->alive = alive;
}

bool _humman_isalive(Human* obj)
{
	return obj->alive;
}

void _humman_set_age(Human* obj, int age)
{
	obj->age = age;
}

int _humman_get_age(Human* obj)
{
	return obj->age;
}

void _humman_destroy(Human* obj)
{
	free(obj);
	obj = NULL;
}

Human* HUM_init()
{
	Human *obj = (Human*)calloc(1, sizeof(Human));

	static struct HUM_Vfunc vfunc = {
		_humman_set_name,
		_humman_get_name,
		_humman_print_info
	};
	//obj->vfunc->print_info = _humman_print_info;
	obj->vfunc = (struct HUM_Vfunc*)&vfunc;

	obj->action = _humman_action;
	obj->set_alive = _humman_set_alive;
	obj->isalive = _humman_isalive;
	obj->set_age = _humman_set_age;
	obj->get_age = _humman_get_age;
	obj->destroy = _humman_destroy;
	return obj;
}

