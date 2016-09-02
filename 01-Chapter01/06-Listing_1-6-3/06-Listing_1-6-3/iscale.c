/*
command line tool that prints a scale with options
iscale [-m] [-i] [-a] N startval [outfile.txt]

-m: interpret startval as a MIDI note (default: interpret as frequency in Hertz)
-i: print interval ratios as well as frequency values (default: print just frequency values)
-a: appends output to outfile.txt instead of overwriting it
outfile.txt: name of (optional) file to output to
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<errno.h>
#include<string.h>

int main(int argc, char* argv[])
{
	// global variables declaration
	int notes, i;
	int ismidi = 0;
	int write_interval = 0;
	int err = 0;
	double startval, basefreq, ratio;
	FILE* fp;
	errno_t errfp;
	int append;
	double intervals[25];
	
	const int buffsize = 512;
	char cmdstring[512];
	cmdstring[0] = '\0';
	
	// stores the cmd line input
	for (int i = 0; i < argc; i++)
	{
		strcat_s(cmdstring, buffsize, argv[i]);
		if (i == 0)
		{
			strcat_s(cmdstring, buffsize, ".exe ");
		}
		else if (i+1 == argc)
		{
			strcat_s(cmdstring, buffsize, "\n");
		}
		else
		{
			strcat_s(cmdstring, buffsize, " ");
		}
	}

	// check for '-' sign (a flag) in argv[i][0] step through the pointer with argv++ and argc--
	while (argc > 1)
	{
		if (argv[1][0] == '-')
		{
			if (argv[1][1] == 'm')
				ismidi = 1;
			else if (argv[1][1] == 'i')
				write_interval = 1;
			else if (argv[1][1] == 'a')
				append = 1;
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
		printf("Usage: iscale [-m] [-i] [-a] N startval [outfile.txt]\n"
			"-m: interpret startval as a MIDI note (default: interpret as frequency in Hertz)\n"
			"-i: print interval ratios as well as frequency values(default: print just frequency values)\n"
			"-a: appends output to outfile.txt instead of overwriting it\n"
			"outfile.txt : name of(optional) file to output to");
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
		if(!append)
			errfp = fopen_s(&fp, argv[3], "w");
		else if (append)
			errfp = fopen_s(&fp, argv[3], "a");

		if (errfp == 0)
			printf("no errors in err: %s\n", err);
		if (fp == NULL)
		{
			printf("WARNING: unable to create file %s\n", argv[3]);
			perror(""); //
		}
	}

	// if we got here the user has been nice and we can perform the operations
	if (ismidi)
	{
		double c0, c5;
		ratio = pow(2.0, 1.0 / 12.0);
		c5 = 220 * pow(ratio, 3);
		c0 = c5 * pow(2.0, -5.0);
		basefreq = c0*pow(ratio, startval);
	}

	else
		basefreq = startval;

	ratio = pow(2.0, 1.0 / notes);
	for (i = 0; i < notes; i++)
	{
		intervals[i] = basefreq;
		basefreq *= ratio;
	}

	for (i = 0; i < notes; i++)
	{
		if (write_interval)
			printf("%d:\t%f\t%f\n", i, pow(ratio, i), intervals[i]);
		else
			printf("%d:\t%f\n", i, intervals[i]);
	}

	if (fp)
	{
		if (append)
		{
			fprintf(fp, "-----------------------------------------\n");
			fprintf(fp, "%s ", cmdstring);
		}

		for (i = 0; i < notes; i++) {
			if (write_interval)
				err = fprintf(fp, "%d:\t%f\t%f\n", i, pow(ratio, i), intervals[i]);
			else
				fprintf("%d:\t%f\n", i, intervals[i]);
			if (err < 0)
				break;
		}
	}
	

	if (err < 0)
		perror("There was an error writing the file.\n");
	if (fp)
		fclose(fp);

	return 0;
}