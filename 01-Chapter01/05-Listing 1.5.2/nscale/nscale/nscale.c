// this program asks for an input from the user and needs to know the octave division (N of notes) and the midinote from which to start from
// it then prints the frequency of the notes that build up the N-tone equal tempered octave

#include<stdio.h>
#include<math.h>

int main(int argc, char* argv[])
{
	// variables declaration
	int notes, midinote;
	double frequency, ratio;
	double c0, c5;
	double intervals[24];

	if (argc != 3)
	{
		printf("usage: nscale notes midinote\n");
		return 1;
	}

	// input validation goes here
	notes = atoi(argv[1]);
	if (notes < 1 || notes > 24)
	{
		printf("Sorry the value is out of range. Select a N-TET between 1 and 24.\n");
		return 1;
	}

	midinote = atoi(argv[2]);
	if (midinote < 0 || midinote > 127)
	{
		printf("Sorry the value is out of range. Select a MIDI note between 0 and 127.\n");
		return 1;
	}


	ratio = pow(2.0, 1.0 / 12.0);	//shouldn't this be divided by N instead of 12?!
	c5 = 220.0 * pow(ratio, 3);		//why is he going by frequency? isn't c5 supposed to be a MIDI note? And why 220 and not 440?
	c0 = c5 * pow(0.5, 5);			// divides by 5 'cause it's 5 octaves down, so frequency-wise one should divide by 2 five times
	frequency = c0 * pow(ratio, midinote);	//finds the frequency corresponding to the user input MIDI note
	
	// for loops logic
	int i;
	for (i = 0; i < notes; i++)
	{
		intervals[i] = frequency;
		frequency *= ratio;
	}
	
	printf("The frequencies of the notes in the octave are:\n");
	for (i = 0; i < notes; i++)
	{
		printf("%d: %f \n", i, intervals[i]);
	}
	
	//TODO: now try with while loops logic - comment the other logics first

	//TODO: and now with do while loops logic - comment the other logics first

	return 0;

}