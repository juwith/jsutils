#include <stdio.h>
#include <cb.h>

void _action_cb(void* pvPrivate, JuCB_ACT_TYPE pvParam)
{
	printf("action cb %d\n",pvParam);
}

void _state_cb(void* pvPrivate, JuCB_STA_TYPE pvParam, char* msg)
{
	printf("state cb %d, %s\n",pvParam,msg);
}

void main()
{
	JuCB *jcb = JuCB_init();
	JuCB_CallBack_T cbt;
	cbt.JuCB_action_cb = _action_cb;
	cbt.JuCB_state_cb = _state_cb;
	JuCB_register_cb(jcb, &cbt);

	JuCB_action(jcb);
	JuCB_state(jcb);

	JuCB_destroy(jcb);
}
