#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv){
    if(argc < 2) {
		return -1;
	}
    srand(clock());
    int n = atoi(argv[1]);
    int count = 0;
    double x, y;
    for(int i = 0; i < n; ++i){
		x = (double)rand() / RAND_MAX;
		//printf("x[%d] = %lf;\n", i,y);
		y = (double)rand() / RAND_MAX;
		//printf("y[%d] = %lf;\n",i, y);
		if(x * x + y * y <= 1) {
			count++;
		}
    }
    return count;
}
