#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char* argv[]) 
{
	// check if the number of argument is correct
	if (argc < 2 || argc > 4) {
		printf("%s converts a frequency into a MIDI note and its pitch percentage deviation\n", argv[0]);
		printf("usage: %s frequency (Atuning) (OctaveDivision)\n", argv[0]);
		printf("frequency range: TBD\n");
		printf("Optional - A tuning range: 415 Hz, 466 Hz (default is 440 Hz)\n");
		printf("Optional - Octave division range: 5-TET, 72-TET (default is 12)\n");
		return 1;
	}
	
	if (argv[2] == NULL) {
		const double a_tuning = 440;		
		const int octavedivision = 12;
	}
	
	if (argv[3] == NULL) {
		if (5 <= atof(argv[2]) <= 72) {
			const double a_tuning = 440;
			const int octavedivision = atof(argv[2]);
		}
		else if (415 <= atof(argv[2]) <= 466) {
			const double a_tuning = atof(argv[2]);
			const int octavedivision = 12;
		}
		else {
			printf("Sorry, the value you entered for either A tuning or for octave division is not correct.\nPlease try again. Thank you.\n");
			return 1;
		}
	}

	if (argv[3] != NULL) {
		if (415 <= atof(argv[2]) <= 466) {
			const double a_tuning = atof(argv[2]);
		}
		else if (atof(argv[2]) < 415 || atof(argv[2]) > 466) {
			printf("Sorry, the value you entered for A tuning is not correct.\nPlease try again. Thank you.\n");
			return 1;
		}
		// TODO: add octave division
	}

	// TODO regex validation on input - is argv[1] a positive double? is there a range and does the input stays whithin?

	// if everything is fine then we can declare the variables we need
	double freq, freq1, freq2, delta, delta1, delta2;
	double deltaMidi1, deltaMidi2;
	double freq2mid, midi2freq, ppd;
	int midinote, pitchpercdev;
	int midi1, midi2;
	const int a4 = 69;

	freq = atof(argv[1]);


	freq2mid = (a4 + (octavedivision*log2(freq/a_tuning)));
	
	midi1 = midinote;
	midi2 = midinote + 1;
	deltaMidi1 = freq2mid - midi1;
	deltaMidi2 = freq2mid - midi2;

	// like a real frequency gentleman would...
	freq1 = pow(2, (double)(midi1 - a4) / (double)octavedivision) * a_tuning;
	freq2 = pow(2, (double)(midi2 - a4) / (double)octavedivision) * a_tuning;
	delta = freq2 - freq1;
	delta2 = freq - freq2;
	delta1 = freq - freq1;
	delta = freq2 - freq1;

	// if if if...
	if (fabs(deltaMidi2) < fabs(deltaMidi1)) {
		ppd = (int)(floor(((delta2 / delta) * 100)));
		midinote = midi2;
	}

	else if (fabs(deltaMidi1) <= fabs(deltaMidi2)) {
		ppd = (int)(floor(((delta1 / delta) * 100)));
		midinote = midi1;
	}



}