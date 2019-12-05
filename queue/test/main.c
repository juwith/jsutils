#include <stdio.h>
#include "queue.h"

int main()
{
	printf("hello world\n");
	Queue *queue = Queue_init();
	Queue_Enqueue(queue,NULL);
	Queue_Dequeue(queue);
	Queue_destroy(queue);
	return 0;
}
