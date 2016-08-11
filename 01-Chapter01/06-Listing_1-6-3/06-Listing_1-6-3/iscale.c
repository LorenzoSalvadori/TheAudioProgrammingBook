/*
command line tool that prints a scale with options
iscale [-m] [-i] N startval [outfile.txt]

-m: interpret startval as a MIDI note (default: interpret as frequency in Hertz)
-i: print interval ratios as well as frequency values (default: print just frequency values)
outfile.txt: name of (optional) file to output to
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char* argv[]) 
{
	// global variables declaration
	int notes, i;
	int ismidi = 0;
	int write_interval = 0;
	int err = 0;
	double startval, basefreq, ratio;
	FILE* fp;
	double intervals[25];

	// check for '-' sign (a flag) in argv[i][0] step through the pointer with argv++ and argc--

	while (argc > 1)
	{
		if (argv[1][0] == '-')
		{
			if (argv[1][1] == 'm')
				ismidi = 1;
			else if (argv[1][1] == 'i')
				write_interval = 1;
			else
			{
				printf("Error: unrecognized option %s\n.", argv[1]);
				return 1;
			}

			argc--;
			argv++;

		}

		else
			break;
	}

	if (argc < 3)
	{
		printf("Error: insufficient arguments.\n");
		printf("Usage: iscale [-m] [-i] N startval [outfile.txt]\n");
		return 1;
	}

	// if we got here we should have the correct amount of arguments to process
	// now on to check if the inputs are whithin range

	notes = atoi(argv[1]);
	if (notes < 1 || notes > 24)
	{
		printf("Error: the number of notes (N) is not in the range 1-24.\n");
		return 1;
	}

	startval = atof(argv[2]);
	if (ismidi)
	{
		if (startval < 0.0 || startval > 127.0)
		{
			printf("Error: the MIDI starting value (startval) is not in the range 0-127.\n");
			return 1;
		}
	}
	else
	{
		if (startval < 0)
		{
			printf("Error: the frequency starting value (startval) is not positive.\n");
			return 1;
		}
	}

	// check for the optional output file
	fp = NULL;
	if (argc == 4) 
	{
		fp = fopen(argv[3], "w");
		if (fp == NULL) 
		{
			printf("WARNING: unable to create file %s\n", argv[3]);
			perror(""); //
		}
	}

	// if we got here the user has been nice and we can perform the operations


}		