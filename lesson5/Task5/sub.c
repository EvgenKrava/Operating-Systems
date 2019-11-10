#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv){
	srand(time(NULL)); 
	FILE * fp;
	char * filename = malloc(sizeof(char) * (strlen(argv[1]) + 8));
	filename = strcat(filename, "file");
	filename = strcat(filename, argv[1]);
	filename = strcat(filename, ".txt");
	
   	/* open the file for writing*/
   	fp = fopen (filename,"w");
	/* write 10 lines of text into the file stream*/
	for(int i = 0; i < atoi(argv[1]); i++){
		fprintf (fp, "%d\n", rand());
	} 
	/* close the file*/  
	fclose (fp);
	free(filename);
}
