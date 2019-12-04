#include "array.h"
#include "space.h"
#include <stdio.h>

void print(array *arr){
	for(int i = 0; i < arr->size; ++i){
		printf("%d ", *(int *)(arr->data[i]));
	}
	printf("\n");
}

int main(){
	int n = 0;
	printf("Input point count\n");
	scanf("%d", &n);
	play(n);
	
	printf("+++++++++++++++++++\n");

	printf("Array\n");
	array *arr = create();
	int a = 1;
	int b = 2;
	int c = 4;
	int d = 5;
	int three  = 3;
	add(arr, &a);
	add(arr, &b);
	add(arr, &c);
	add(arr, &d);
	insert(arr, 2, &three);
	print(arr);
	return 0;
}
