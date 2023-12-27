package src;

import java.util.ArrayList;

public class Maxsub {
	public static int maxsub(int[] A, int n) 
	{  int ans = 0, cnt = 0; 
	   for (int i = 0; i < n; i ++) { 
		   cnt += A[i]; 
		   if (cnt < 0)  
			  cnt=0; // should be cnt = 0; 
		   if (cnt > ans) 
			   ans = cnt; 
		}  
	    return ans; 
	 } 	

	/**
	 * Call maxsub
	 *
	 * @param arr
	 * @return
	 */
	public static int max_sub(ArrayList<Integer> arr) {
		int[] A = new int[arr.size()];
		int n = arr.size();
		return maxsub(A, n);
	}
}
