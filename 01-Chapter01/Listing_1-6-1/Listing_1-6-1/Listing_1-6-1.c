#include<stdio.h>

void main()
{
	double buffer[1024];
	double* ptr = buffer + 1024;
	double maxval = 0.0;
	unsigned long pos = 0;

	while (--ptr >= buffer)
	{
		if (*ptr >= maxval)
		{
			maxval = *ptr;
			pos = ptr - buffer;
		}
	}

	printf("The maximum sample i %f, at position %d\n", maxval, pos);
	
	return 0;
}