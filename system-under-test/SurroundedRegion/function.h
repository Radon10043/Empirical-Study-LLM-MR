// A C++ program to replace all 'O's with 'X''s if surrounded by 'X' 
#include<iostream> 
#include <limits.h>
#include<string>
#include <dirent.h>
#include <vector>

// Size of given matrix is M X N 
// A recursive function to replace previous value 'prevV' at '(x, y)' 
// and all surrounding values of (x, y) with new value 'newV'. 
void floodFillUtil(int M,int N,char mat[][900], int x, int y, char prevV, char newV) 
{ 
	// Base cases 
	if (x < 0 || x >= M || y < 0 || y >= N) 
		return; 
	if (mat[x][y] != prevV) 
		return; 

	// Replace the color at (x, y) 
	mat[x][y] = newV; 

	// Recur for north, east, south and west 
	floodFillUtil(M,N,mat, x+1, y, prevV, newV); 
	floodFillUtil(M,N,mat, x-1, y, prevV, newV); 
	floodFillUtil(M,N,mat, x, y+1, prevV, newV); 
	floodFillUtil(M,N,mat, x, y-1, prevV, newV); 
} 

// Returns size of maximum size subsquare matrix 
// surrounded by 'X' 
void replaceSurrounded(int M,int N,char mat[][900]) 
{ 
// Step 1: Replace all 'O' with '-' 
for (int i=0; i<M; i++) 
	for (int j=0; j<N; j++) 
		if (mat[i][j] == 'O') 
			mat[i][j] = '-'; 

// Call floodFill for all '-' lying on edges 
for (int i=0; i<M; i++) // Left side 
	if (mat[i][0] == '-') 
		floodFillUtil(M,N,mat, i, 0, '-', 'O'); 
for (int i=0; i<M; i++) // Right side 
	if (mat[i][N-1] == '-') 
		floodFillUtil(M,N,mat, i, N-1, '-', 'O'); 
for (int i=0; i<N; i++) // Top side 
	if (mat[0][i] == '-') 
		floodFillUtil(M,N,mat, 0, i, '-', 'O'); 
for (int i=0; i<N; i++) // Bottom side 
	if (mat[M-1][i] == '-') 
		floodFillUtil(M,N,mat, M-1, i, '-', 'O'); 

// Step 3: Replace all '-' with 'X' 
for (int i=0; i<M; i++) 
	for (int j=0; j<N; j++) 
		if (mat[i][j] == '-') 
			mat[i][j] = 'X'; 

} 



