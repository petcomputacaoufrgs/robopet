#pragma once


/**
 * Macro for debugging any variable.
 * 
 * \ingroup RoboPETLib
 */ 
#define DEBUG_VAR(x) cout << #x << ": " << x << endl

/**
 * Macro for debugging lines of the code.
 * 
 * \ingroup RoboPETLib
 */ 
#define DEBUGL(x) cout << __FUNCTION__ << ": line " << __LINE__ << endl

/**
 * Allocate contiguous space for dynamic matrixes.
 * @param sizex Dimension x of the matrix
 * @param sizey Dimension y of the matrix
 * @param typeSize Size of the matrix type. Use sizeof(<matrix_type>) when calling
 * @return The variable storing the matrix
 * \ingroup RoboPETLib
 */
void** allocMatrix(int sizex, int sizey, int typeSize);
