#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int run_error_check(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	// Value user entered as int
	int seconds = run_error_check(argc, argv);

	for (int i = seconds; i > 0; i--) {
		printf("\033[2K\rTimer was set for %i seconds", i); // \033[2K clears the line
		fflush(stdout);
		sleep(1);
	}
	printf("\033[2K\rTime's up!\n");

	return 0;
}

int run_error_check(int argc, char *argv[]) {
	// Check for only 1 argument
	// Do this check before assigning seconds
	if (argc != 2) {
		printf("You should be entering a single value!\n");
		exit(1);
	}
	// Check if it's a number
	int start = (argv[1][0] == '-') ? 1 : 0; // Check if first char is -; If yes then skip
    for (int i = start, n = strlen(argv[1]); i < n; i++) {
		if (!isdigit(argv[1][i])) {
			printf("You should be entering a number!\n");
			exit(2);
		}
	}
	int seconds = atoi(argv[1]);
	// Check for argument not being -ve
	if (seconds < 0) {
		printf("Number should be greater than 0... Negative time isn't possible yet!\n");
		exit(3);
	}
	return seconds;
}
