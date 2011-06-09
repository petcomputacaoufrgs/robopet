#include <stdlib.h>

#include "utils.h"

void** allocMatrix(int sizex, int sizey, int typeSize)
{
	void** matrix;
	
	matrix = (void**) calloc(sizex, 4);
	for(int i=0; i<sizex; i++)
		matrix[i] = (void*) calloc(sizey, typeSize);
		
	return matrix;	
}
