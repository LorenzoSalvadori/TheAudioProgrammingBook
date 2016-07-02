/* freq 2 midi, exercise 1.3.2 of chapter 1, page 88, the audio programming book*/

/* This is a program that gets a frequency from the user and turns it into a MIDI note number
   including the pitch deviation percentage
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main() 
{
	int midinote, ppd, midi1, midi2;
	double frequency, freq2mid, midi2freq, pitchdeviation, delta, delta1, delta2, f, f1, f2;
	char message[256];	// here we store the user input
	char* result;		// here we point at the user input to check wether errors happen
	
	// let's get the input from the user and store its value in message
	// and its memory location in the result pointer
	printf("Hola! Type a frequencia in Hz that you would like to convert in MIDI note: ");
	result = gets(message);

	// let's check the user is not acting bad
	if (result == NULL) {
		printf("Please enter something or hit return.\n");
		//return 1;
		printf("Press ashuafhgsja to continue...\n");
		getchar();
		main();
	}

	if (message[0] == '\0') {
		printf("Alright then, I should have known better.\nYou run me and then you just leave me whithout saying anyting.\nYou are just like all the other programmers.");
		//return 1;
		printf("Now... press ashuafhgsja to continue...\n");
		getchar();
		main();
	}

	// let's convert the message into a usable value
	frequency = atof (message);

	if (frequency < 0) {
		printf("Oh, come on! Really?! You know frequencies have to be positive do you?! DUH??!\n");
		
		printf("Now... press ashuafhgsja to continue...\n");
		getchar();
		main();
	}

	if (frequency == 0) {
		printf("Everything is calm...");
		
		printf("Now... press ashuafhgsja to continue...\n");
		getchar();
		main();
	}

	// let's do some math now! Midis first...
	freq2mid = (69 + (12 * log2(frequency / 440))) + 0.5;
	midinote = (int)freq2mid;
	midi1 = midinote;
	midi2 = midinote + 1;
	midi2freq = pow(2, (double)(midinote - 69) / (double)12) * 440;

	// like a real frequency gentleman would...
	f = frequency;
	f1 = pow(2, (double)(midi1 - 69) / (double)12) * 440;
	f2 = pow(2, (double)(midi2 - 69) / (double)12) * 440;
	delta2 = f - f2;
	delta1 = f - f1;
	delta = f2 - f1;
	
	// if if if...
	if (delta2 < delta1){
		ppd = (int)((delta2/delta) *100);
		midinote = midi2;
	}
	
	else if (delta1 < delta2){
		ppd = (int)((delta1/delta) *100);
		midinote = midi1;
	}

	
	printf("The MIDI note corresponding to the frequency you entered is: %d\n", midinote);
	printf("and its pitch deviation percentage is: %d%%.\n", ppd);
	printf("It's been a pleasure working with you. Have a nice day!\n");
	getchar();
	return 0;

}