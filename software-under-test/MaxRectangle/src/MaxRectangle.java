package src;
import java.util.ArrayList;
import java.util.Stack;


public class MaxRectangle {

	public static int maximalRectangle(ArrayList<ArrayList<Integer>> a) {
        int area = 0;
        int m = a.size();
        int n = a.get(0).size();
        int i, j;
        int[][] s = new int[m][n];
        
        for(i = 0; i < m; i++){
            for(j = 0; j < n; j++){
                if(a.get(i).get(j) == 1)
                    s[i][j] = (i == 0) ? 1 : s[i-1][j] + 1;
                else
                    s[i][j] = 0;
            }
        }
        
        for(i =0; i < m; i++)
            area = Math.max(area, largestRectangleArea(s[i]));
        return area;
    }
    
    public static int largestRectangleArea(int[] heights){
        if(heights == null || heights.length == 0)
            return 0;
        
        Stack<Integer> stack = new Stack<Integer>();
        int max = 0;
        
        int i = 0;
        
        while(i < heights.length){
            if(stack.isEmpty() || heights[stack.peek()] <= heights[i]){
                stack.push(i);
                i++;
            }
            else{
                int height = heights[stack.pop()];
                int width = stack.isEmpty() ? i : i - stack.peek() - 1;
                max = Math.max(max, height * width);
            }
        }
        
        while(!stack.isEmpty()){
            int height = heights[stack.pop()];
            int width = stack.isEmpty() ? i : i - stack.peek() -1;
            max = Math.max(max, height * width);
        }
        return max;
    }
    public static int min(int a, int b, int c){
        int m = Math.min(a, b);
        m = Math.min(m, c);
        return m;
    }
	
}
