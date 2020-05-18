#include <stdio.h>

int main()
{
	int *ptr = NULL;
	*ptr = 1; //segmentation fault.
	return 0;
}
