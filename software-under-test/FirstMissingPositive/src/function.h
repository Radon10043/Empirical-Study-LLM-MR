#ifndef _HAVE_FUNCTION_H
#define _HAVE_FUNCTION_H

#include <iostream>
#include <vector>

int firstMissingPositive(int nums[],int n) {
        for (int i = 0; i < n; ++i) {
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                std::swap(nums[i], nums[nums[i] - 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) return i + 1;
        }
        return n + 1;
}

/**
 * @brief Find the first missing positive integer
 * 
 * @param nums 
 * @return int 
 */
int first_missing_positive(std::vector<int> nums) {
    return firstMissingPositive(nums.data(), nums.size());
}

#endif