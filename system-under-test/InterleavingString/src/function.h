#ifndef _HAVE_FUNCTION_H
#define _HAVE_FUNCTION_H

#include <string>
using namespace std;

bool isInterleaved(char* A, char* B, char* C) 
{ 
    if (!(*A || *B || *C)) 
        return true; 
  
    if (*C == '\0') 
        return false; 

    return ((*C == *A) && isInterleaved(A + 1, B, C + 1)) 
           || ((*C == *B) && isInterleaved(A, B + 1, C + 1)); 
} 

/**
 * @brief Check whether C is the interleaving of A and B
 *
 * @param A
 * @param B
 * @param C
 * @return true
 * @return false
 */
bool is_interleaved(string& A, string& B, string& C) {
    return isInterleaved(&A[0], &B[0], &C[0]);
}

#endif