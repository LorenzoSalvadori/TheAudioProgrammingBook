/* strtol example */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */

int main()
{
	float number;
	char message[256];
	char* result;
	result = gets(message);

	number= strtol(message, &result, 10);

	printf("Converted number is: %d\n", number);
	getch();
	return 0;
	/*
	char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
	char * pEnd;
	long int li1, li2, li3, li4;
	li1 = strtol(szNumbers, &pEnd, 10);
	li2 = strtol(pEnd, &pEnd, 16);
	li3 = strtol(pEnd, &pEnd, 2);
	li4 = strtol(pEnd, NULL, 0);
	printf("The decimal equivalents are: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);
	return 0;*/
}