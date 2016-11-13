#include <stdio.h>
#include "ppmio.h"

int main () {
	
	int ***M, *size, i, j, k;
	M = readImage ("img.ppm");
	size = getSize ("img.ppm");
	writeImage (M, size[0], size[1], "new.ppm");
	freeImage (M, size[0], size[1]);
	freeSize(size);
	return 0;
}