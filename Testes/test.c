#include <stdio.h>
#include "ppmio.h"

int main () {
	
	ppmimg M;
	int i, j, k;
	M = readImage ("img.ppm");
	writeImage (M, "new.ppm");
	freeImage (M);
	return 0;
}