#include <stdlib.h>

#include "utils.h"

void** allocMatrix(int sizex, int sizey, int typeSize, int typePtrSize)
{
	void** matrix;
	
	matrix = (void**) calloc(sizex, typePtrSize);
	for(int i=0; i<sizex; i++)
		matrix[i] = (void*) calloc(sizey, typeSize);
		
	return matrix;	
}

char* itoa(int value, char* result, int base) {
/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}
