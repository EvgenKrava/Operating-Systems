#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#define DOT_COUNT 15

int main (void) {
	int i, status;
	/* Child */
	if (!fork()) {
		for (i = 0; i < DOT_COUNT; i++) {
			fprintf(stderr, ".");
			sleep(1);
		}
		exit(5);
	}
	/* Parent */
	while (1) {
		if (!waitpid(-1, &status, WNOHANG)) {
			fprintf(stderr, "*");
		} else {
			fprintf(stderr, "(exit)\n");
			break;
		}
		sleep(2);
	}
	if (WIFEXITED (status)) {
		fprintf(stderr, "Exited with code=%d\n", WEXITSTATUS(status));
	} else if (WIFSIGNALED (status)) {
		fprintf(stderr, "Exited by signal\n");
	}
	return EXIT_SUCCESS;
}
