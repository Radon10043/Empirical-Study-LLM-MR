#ifndef _HAVE_FUNCTION_H
#define _HAVE_FUNCTION_H

bool isInterleaved(char* A, char* B, char* C) 
{ 
    if (!(*A || *B || *C)) 
        return true; 
  
    if (*C == '\0') 
        return false; 

    return ((*C == *A) && isInterleaved(A + 1, B, C + 1)) 
           || ((*C == *B) && isInterleaved(A, B + 1, C + 1)); 
} 

#endif