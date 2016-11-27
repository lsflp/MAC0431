#include <stdio.h>
#include "ppmio/ppmio.h"

int main () {
	
	ppmimg M;
	int i, j, k;
	M = readImage ("Bali.ppm");
	printf("Li o arquivo.\n");
	writeImage (M, "new.ppm");
	freeImage (M);
	return 0;
}