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
	// step through code with argv++ and argc-- to check for '-' sign (a flag) in argv[i][0]

	// if there is a flag
		// if the flag is m
			// set MIDI option
		
		//  else if the flag is i
			// set interval option

		// else
			// report an incorrect flag error


	
}		