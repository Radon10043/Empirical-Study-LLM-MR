#ifndef _HAVE_FUNCTION_H
#define _HAVE_FUNCTION_H

#include<string>
  
int min(int x, int y, int z) 
{ 
   int result=x;
   if(y<result)
   result=y;
   if(z<result)
   result=z;
   return result;
} 
  
int editDist(std::string str1 ,std::string str2 , int m ,int n) 
{ 

    if (m == 0) return n;  
    if (n == 0) return m; 
    if (str1[m-1] == str2[n-1]) 
        return editDist(str1, str2, m-1, n-1);   
    return 1 + min ( editDist(str1,  str2, m, n-1), 
                     editDist(str1,  str2, m-1, n), 
                     editDist(str1,  str2, m-1, n-1) 
                   ); 
} 

/**
 * @brief Count the minimum number of operations required to transform str1 to str2
 *
 * @param str1
 * @param str2
 * @return int
 */
int edit_dist(std::string& str1, std::string& str2) {
    return editDist(str1, str2, str1.length(), str2.length());
}

#endif