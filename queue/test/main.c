#include <stdio.h>
#include "queue.h"

int main()
{
	printf("hello world\n");
	int data = 1;
	Queue *queue = Queue_init();
	Queue_Enqueue(queue,&data);
	int* deq = (int*)Queue_Dequeue(queue);
	printf("%d\n",*deq);

	Queue_destroy(queue);
	return 0;
}
