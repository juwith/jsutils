#include <stdio.h>
#include <stdbool.h>
#include <humman.h>

void main()
{
	Human* hum = HUM_init();
	HUM_action(hum);
	HUM_set_age(hum,30);
	int age = HUM_get_age(hum);
	printf("get hum age %d\n",age);

	HUM_set_alive(hum,true);
	bool alive = HUM_isalive(hum);
	printf("%s\n",alive ? "alive" : "died");

	char* name = "hello";
	HUM_set_name(hum,name);
	printf("name is %s\n",HUM_get_name(hum));

	HUM_print_info(hum);
}
