
/**
 * Function used to allocate space for dynamic matrixes.
 * @param sizex Dimension x of the matrix
 * @param sizey Dimension y of the matrix
 * @param typeSize Size of the matrix type. Use sizeof(<matrix_type>) when calling
 * @return The variable storing the matrix
 */
void** allocMatrix(int sizex, int sizey, int typeSize);
