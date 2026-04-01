#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#define PI 3.14159265358979323846

int run_error_check(int argc, char *argv[]);
void flag_parser(int argc, char *argv[]);
void beep();
void hangup();

static bool M_FLAG = false;
static char *M_FLAG_VALUE = "\0"; 
static bool A_FLAG = false;

int main(int argc, char *argv[]) {
	// Check the flags passed by user
	flag_parser(argc, argv);
	// Value user entered as int
	int seconds = run_error_check(argc, argv);

	for (int i = seconds; i > 0; i--) {
		const char* label = (i == 1) ? "second" : "seconds";
		printf("\033[2K\r%i %s remaining", i, label); // \033[2K clears the line
		fflush(stdout);
		sleep(1);
	}
	if (!M_FLAG) {
		printf("\033[2K\rTime's up!\n");
	}
	else {
		printf("\033[2K\r%s\n", M_FLAG_VALUE);
	}
	if (A_FLAG) {
		hangup();
	}

	return 0;
}

int run_error_check(int argc, char *argv[]) {
	// Do this check before assigning seconds
	if (argc < 2) {
		printf("You look like you know what you're doing...\n\nUsage: tt <seconds> [OPTIONS]\n");
		printf("Currently supported: -a, -m <message>\n");
		exit(5);
	}
	if (argc > 5) {
		printf("Trying something fishy, eh?\n");
		exit(6);
	}

	bool FLAG_KNOWN = argv[1][1] == 'a' || argv[1][1] == 'm';
	bool INVALID_ARG = !isdigit(argv[1][0]);
	if (INVALID_ARG && FLAG_KNOWN) {
		printf("What seconds?\n");
		exit(1);
	}
	// Check if it's a number
	int start = (argv[1][0] == '-') ? 1 : 0; // Check if first char is -; If yes then skip
    for (int i = start, n = strlen(argv[1]); i < n; i++) {
		if (!isdigit(argv[1][i])) {
			printf("That's not even close to a number.\n");
			exit(2);
		}
	}
	int seconds = atoi(argv[1]);
	// Check for argument not being -ve
	if (seconds < 0) {
		printf("Negative time isn't possible.\n\nYet...\n");
		exit(3);
	}
	return seconds;
}

void flag_parser(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'm') {
				M_FLAG = true;
				if (argv[i+1]) {
					M_FLAG_VALUE = argv[i+1];
				} else {
					printf("You forgot the message you muppet.\n");
					exit(4);
				}
			}
			if (argv[i][1] == 'a') {
				A_FLAG = true;
			}
		}
	}
}

void beep() {
	FILE *dsp = fopen("/dev/dsp", "wb");
	if (!dsp) {
		printf("No /dev/dsp found. You're not caveman enough.\n");
		exit(5);
	}

	int sample_rate = 8000;
	float freq = 440.0;      // standard A note
	float duration = 0.5;    // half second
	int samples = (int)(sample_rate * duration);

	for (int i = 0; i < samples; i++) {
		unsigned char sample = (unsigned char)(
			127.5 + 127.5 * sin(2.0 * PI * freq * i / sample_rate)
		);
		fwrite(&sample, 1, 1, dsp);
	}
	fclose(dsp);
}

void hangup() {
	for (int i = 0; i < 5; i++) {
		beep();
		usleep(500000); // 0.5 seconds
	}
}
