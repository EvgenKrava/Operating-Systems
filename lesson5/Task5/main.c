#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* записываем знак */
         n = -n;          /* делаем n положительным числом */
     i = 0;
     do {       /* генерируем цифры в обратном порядке */
         s[i++] = n % 10 + '0';   /* берем следующую цифру */
     } while ((n /= 10) > 0);     /* удаляем */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }


char *systemVariableName = "FILE_NAME";

int main(int argc, char **argv) {
	const struct option long_opt[] = {
		{"file", 1, 0, 'f'},
		{"number", 1, 0, 'n'},
		{NULL,0,NULL,0}
	};
	int n = 0;	
	char c;
	while ((c = getopt_long(argc, argv, "f:n:", long_opt, NULL)) != -1) {
		switch(c){
			case 'f':
				systemVariableName = malloc(strlen(optarg) * sizeof(char));
				systemVariableName = strcpy(systemVariableName, optarg);
				break;
			case 'n':
				n = atoi(optarg);
				break;
			case '?':
				fprintf(stderr, "%s\n", "Unknown option");
				break;
		}
	}
	printf("System variable name: %s\n", systemVariableName);
	printf("Proccess count: %d\n", n);
	char *s = malloc(sizeof(char) * 255);
	s = strcat(s, "FILE_NAME=");
	s = strcat(s, systemVariableName);
	putenv(s);
	for(int i = 1; i <= n; ++i) {
		if(fork() == 0) { 
			char p[17];
			itoa (i, p);
        	char *args[]={"./sub", p, getenv("FILE_NAME") , NULL}; 
        	execvp(args[0], args); 
    }
	}
	free(systemVariableName);
	free(s);
	return EXIT_SUCCESS; /* exit(0); */
}
