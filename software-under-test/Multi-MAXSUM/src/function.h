#ifndef _HAVE_FUNCTION_H
#define _HAVE_FUNCTION_H

#include <iostream>
#include <vector>
using namespace std;

int max(int a,int c)
{
	return a>c ? a:c;
}
int solve(int dp[],int num[],int n,int m)
{
	for(int i=1;i<=m;i++)
	{
		int step=0;
		for(int k=1;k<=i;k++)
			step+=num[k];
		dp[n]=step;
		for(int j=i+1;j<=n;j++)
		{
			step=max(step,dp[j-1])+num[j];
			dp[j-1]=dp[n];
			dp[n]=max(step,dp[n]); 
		}
	}
	return dp[n];
}

/**
 * @brief Find m contiguous mutex subarray with the largest sum
 *
 * @param nums
 * @param m
 * @return int
 */
int multi_maxsum(vector<int> nums, int m) {
	int n = nums.size();
	vector<int> dp(n);
	return solve(dp.data(), nums.data(), n - 1, m);
}

#endif