> ### `max_sub` Function Specification
>
> #### Description
> The `max_sub` function calculates the maximum subarray sum within an array of integers. This problem is also known as the "Maximum Subarray Problem," where the goal is to find the contiguous subarray (containing at least one number) which has the largest sum among all subarrays.
>
> #### Function Signatures
> Java Version (Array Input):
> ```java
> public static int maxsub(int[] A, int n)
> ```
>
> Java Version (ArrayList Input):
> ```java
> public static int max_sub(ArrayList<Integer> arr)
> ```
>
> #### Parameters
> - `A`: An array of integers representing the input sequence for the `maxsub` function.
> - `n`: The size of the array `A`.
> - `arr`: An `ArrayList<Integer>` representing the input sequence for the `max_sub` function.
>
> #### Returns
> - Both versions return an `int` representing the sum of the maximum subarray found within the input sequence.
>
> #### Logic
> - **Initialization**: The function initializes two variables, `ans` and `cnt`, to 0. `ans` is used to keep track of the maximum sum encountered so far, and `cnt` is used to store the current sum while iterating through the array.
> - **Iteration**: For each element in the array, it adds the element to `cnt`. If `cnt` becomes negative, it is reset to 0, as a negative sum can't contribute to the maximum sum of a subsequent subarray. If `cnt` is greater than `ans`, `ans` is updated with the value of `cnt`.
> - **Reset on Negative Sum**: Resetting `cnt` to 0 upon encountering a negative sum allows the algorithm to effectively ignore the previous elements, as they cannot contribute to a new maximum sum.
> - **Max Sum Update**: The `ans` variable is updated only if the current sum (`cnt`) is greater than the current maximum (`ans`).
>
> #### Notes
> - This implementation of the Maximum Subarray Problem uses Kadane's Algorithm, which is an efficient way to solve the problem with a time complexity of O(n), where n is the number of elements in the input array.
> - The function `max_sub` serves as a wrapper that converts an `ArrayList<Integer>` to an array, allowing the `maxsub` logic to be applied to data in `ArrayList` form. This conversion ensures compatibility with different types of collections in Java.
> - The algorithm assumes that the input array contains at least one integer. If the array consists only of negative numbers, the maximum subarray sum is 0, as the algorithm would choose not to take any element to maximize the sum.