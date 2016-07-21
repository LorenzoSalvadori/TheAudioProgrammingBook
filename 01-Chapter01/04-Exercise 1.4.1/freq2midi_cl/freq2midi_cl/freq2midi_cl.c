#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char* argv[]) 
{
	// check if the number of argument is not correct
	if (argc < 2 || argc > 4) { //print error
		printf("%s converts a frequency into a MIDI note and its pitch percentage deviation\n", argv[0]);
		printf("usage: %s frequency (Atuning) (OctaveDivision)\n", argv[0]);
		printf("frequency range: TBD\n");
		printf("Optional - A tuning range: 415 Hz, 466 Hz (default is 440 Hz)\n");
		printf("Optional - Octave division range: 5-TET, 72-TET (default is 12)\n");
		return 1;
	}

	// validation on input - is argv[1] a double? is argv[2] a double? is argv[3] an int?
	if (atof(argv[1]) == 0 && *argv[1] != '0') { //print error
		printf("Sorry, the first value you entered is not in the correct format.\nPlease try again. Thank you.\n");
		return 1;
	}

	if (argv[2] != NULL && atof(argv[2]) == 0 && *argv[2] != '0') { //print error
		printf("Sorry, the second value you entered is not in the correct format.\nPlease try again. Thank you.\n");
		return 1;
	}
	
	if (argv[3] != NULL && atof(argv[3]) == 0 && *argv[3] != '0') { //print error
		printf("Sorry, the third value you entered is not in the correct format.\nPlease try again. Thank you.\n");
		return 1;
	}

	// define ranges for A-tuning and octave division, and their defaults
	const int atune_min = 415;
	const int atune_max = 466;
	const int od_min = 5;
	const int od_max = 72;
	const int atune_default = 440;
	const int od_default = 12;
	double a_tuning;
	int octavedivision;

	// if no option for A-tuning was specified then use default ones
	if (argv[2] == NULL) {
		a_tuning = atune_default;	
		octavedivision = od_default;
	}
	
	// if one option is specified then check whether it is in the A-tuning range or in the octave division range
	// then assign the input accordingly, and the default value to the other
	if (argv[3] == NULL) {
		if (od_min <= atoi(argv[2]) <= od_max) {
			a_tuning = atune_default;
			octavedivision = atoi(argv[2]);
		}
		else if (atune_min <= atof(argv[2]) <= atune_max) {
			a_tuning = atof(argv[2]);
			octavedivision = od_default;
		}
		else { //print error
			printf("Sorry, the value you entered for either A tuning or for octave division is not correct.\nPlease try again. Thank you.\n");
			return 1;
		}
	}

	// if both options are specified check that each one is whithin range and then assign the values accordingly
	if (argv[3] != NULL) {
		// tuning division
		if (atune_min <= atof(argv[2]) <= atune_max) {
			a_tuning = atof(argv[2]);
		}
		else if (atof(argv[2]) < atune_min || atof(argv[2]) > atune_max) { //print error
			printf("Sorry, the value you entered for A tuning is not whithin the allowed range.\nPlease try again. Thank you.\n");
			return 1;
		}
		// octave division
		if (od_min <= atoi(argv[3]) <= od_max) {
			octavedivision = atoi(argv[3]);
		}
		else if (atoi(argv[3]) < od_min || atoi(argv[3]) > od_max) { //print error
			printf("Sorry, the value you entered for the octave division is not whithin the allowed range.\nPlease try again. Thank you.\n");
			return 1;
		}
	}

	// if everything is fine then we can declare the variables we need
	double freq, freq1, freq2, delta, delta1, delta2;
	double deltaMidi1, deltaMidi2;
	double freq2mid, midi2freq, ppd;
	int midinote, pitchpercdev;
	int midi1, midi2;
	const int a4 = 69;

	freq = atof(argv[1]);


	freq2mid = (a4 + (octavedivision*log2(freq/ a_tuning)));
	midinote = (int)freq2mid;

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