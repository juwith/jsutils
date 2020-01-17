/**
 * @file humman.h
 * @author Jusang Maeng (jusang6900@gmail.com)
 * @date 2020.01.17
 * @brief template for c programming
 * based on object oriented programming(OOP)
 * use doxygen\n
 * create library\n
 * create binrary that use library\n
 * create pkg-config\n
 * use other project pkg-config\n
 * @see https://juwith.blogspot.com/
 */

#ifndef __BASE_OBJECT_H__
#define __BASE_OBJECT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct Human Human;

struct Human
{
	//private data
	char name[128];
	bool alive;
	int age;

	//virtual func
	struct HUM_Vfunc *vfunc;

	//public function
	void (*action)(struct Human* obj);
	void (*set_alive)(struct Human* obj, bool alive);
	bool (*isalive)(struct Human* obj);

	void (*set_age)(struct Human* obj,int age);
	int (*get_age)(struct Human* obj);
	void (*destroy)(struct Human* obj);
};

//virtual function
struct HUM_Vfunc
{
	void (*set_name)(Human* obj,char* name);
	char* (*get_name)(Human* obj);
	void (*print_info)(Human* obj);
};

/**
 * @brief HUM_set_name
 *
 * user can set name of human.
 *
 * @param Human human object(class)
 * @param char* human name
 * @return void
 */
static inline void HUM_set_name(Human *obj,char* name)
{
	obj->vfunc->set_name(obj,name);
}

/**
 * @brief HUM_get_name
 *
 * user can get name of human
 *
 * @param Human human object(class)
 * @return char*
 */
static inline char* HUM_get_name(Human *obj)
{
	return obj->vfunc->get_name(obj);
}

/**
 * @brief HUM_print_info
 *
 * print human info, name, age, alive
 *
 * @param Human human object(class)
 * @return void
 */
static inline void HUM_print_info(Human *obj)
{
	obj->vfunc->print_info(obj);
}

/**
 * @brief HUM_action
 *
 * do action
 *
 * @param Human human object(class)
 * @return void
 */
static inline void HUM_action(Human *obj)
{
	obj->action(obj);
}

/**
 * @brief HUM_set_alive
 *
 * user can set alive or not
 *
 * @param Human human object(class)
 * @param bool alive true : alive, false : died
 * @return void
 */
static inline void HUM_set_alive(Human *obj, bool alive)
{
	obj->set_alive(obj,alive);
}

/**
 * @brief HUM_isalive
 *
 * user can get human alive or not
 *
 * @param Human human object(class)
 * @return bool
 */
static inline bool HUM_isalive(Human *obj)
{
	return obj->isalive(obj);
}

/**
 * @brief HUM_set_age
 *
 * user can set human age
 *
 * @param Human human object(class)
 * @param int age
 * @return void
 */
static inline void HUM_set_age(Human *obj, int age)
{
	obj->set_age(obj,age);
}

/**
 * @brief HUM_get_age
 *
 * user can get human age
 *
 * @param Human human object(class)
 * @return int
 */
static inline int HUM_get_age(Human *obj)
{
	return obj->get_age(obj);
}

/**
 * @brief HUM_destroy
 *
 * destroy object
 *
 * @param Human human object(class)
 * @return int
 */
static inline void HUM_destroy(Human *obj)
{
	obj->destroy(obj);
}

/**
 * @brief HUM_init
 *
 * create object
 *
 */
Human* HUM_init();
#ifdef __cplusplus
}
#endif
#endif
