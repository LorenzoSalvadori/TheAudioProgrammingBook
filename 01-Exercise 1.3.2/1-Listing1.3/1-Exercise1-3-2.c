/* freq 2 midi, exercise 1.3.2 of chapter 1, page 88, the audio programming book*/

/* This is a program that gets a frequency from the user and turns it into a MIDI note number
   including the pitch deviation percentage
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main() 
{
	int midinote, ppd;
	double frequency, freq2mid, pitchdeviation;
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

	// let's do some math now
	freq2mid = (69 + (12 * log2(frequency / 440))) + 0.5;
	midinote = (int)freq2mid;

	// this next calc is WRONG!! also need some way to convert back midi to freq... -_-
	pitchdeviation = freq2mid - (double)midinote;

	if (pitchdeviation > 0.5) {
		midinote ++;
	}

	// pitch percentage deviation is...
	ppd = (int)((freq2mid - (double)midinote) * 100);

	printf("The MIDI note corresponding to the frequency you entered is: %d\n", midinote);
	printf("and its pitch deviation percentage is: %d%%.\n", ppd);
	printf("It's been a pleasure working with you. Have a nice day!\n");
	getchar();
	return 0;

}