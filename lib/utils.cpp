#include <stdlib.h>

#include "utils.h"

void** allocMatrix(int sizex, int sizey, int typeSize)
{
	void** matrix;
	
	matrix = (void**) malloc(typeSize*sizex);
	for(int i=0; i<sizex; i++)
		matrix[i] = malloc(typeSize*sizey);
		
	return matrix;	
}
