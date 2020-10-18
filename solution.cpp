#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <utility> // pair
#include <tuple>
#include <algorithm>
#define MINUS_INT_MAX INT_MAX * (-1);

/*
    Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
    Output: 6
    Explanation: [4,-1,2,1] has the largest sum = 6.
*/

class Solution {
public:

    bool isAllLessThanZero(std::vector<int>& nums) {
        sort(nums.begin(), nums.end(), std::greater<int>());
        return nums[0] >= 0;
    }

    int maxSubArrayDP(std::vector<int>& nums) {
        // boundary condition
        if(nums.size() <= 0) {
            return INT_MAX * (-1);
        }
        if(nums.size() == 1) {
            return nums[0];
        }
        printf("[\t");
        for(int i = 0 ; i < nums.size() ; i++)
            printf("%d\t", nums[i]);
        printf("]\n");

        // check if all the numbers are less than zero
        std::vector<int> tmp_nums = nums;
        sort(tmp_nums.begin(), tmp_nums.end(), std::greater<int>());

        printf("after sort\n[\t");
        for(int i = 0 ; i < tmp_nums.size() ; i++)
            printf("%d\t", tmp_nums[i]);
        printf("]\n");

        if(tmp_nums[0] <= 0) {
            return tmp_nums[0];
        }

        // if not all teh numbers are less than zero
        // initialize the variable
        int max_value = MINUS_INT_MAX;
        int curr_sum = 0;

        // solutions
        printf("[i] curr sum\tmax value\n");
        for(int i = 0 ; i < nums.size() ; i++) {
            curr_sum += nums[i];
            curr_sum  = std::max(0, curr_sum);
            max_value = std::max(curr_sum, max_value);
            printf("[%d] %d\t\t%d\n", i, curr_sum, max_value);
        }
        return max_value;
    }


    int _DivideAndConquerGetCrossMax(std::vector<int>& nums, int start, int mid_idx, int end) {

        /*

            [ ][ ] | [ ][ ][ ]
             <- ^     ^ ->
             left     right
        */  

        int leftMax = nums[mid_idx];
        int leftSum = 0;
        int rightMax = nums[mid_idx + 1];
        int rightSum = 0;
        printf("find left max\n");
        for (int i = mid_idx; i >= start; i--)
        {
            printf("%d\t", nums[i]);
            leftSum += nums[i];
            leftMax = std::max(leftMax, leftSum);
        }
        printf("\nfind right max\n");
        for (int i = mid_idx + 1; i <= end; i++)
        {
            printf("%d\t", nums[i]);
            rightSum += nums[i];
            rightMax = std::max(rightMax, rightSum);
        }
        
        int max = std::max(std::max(leftMax, rightMax), leftMax + rightMax);
        printf("\n========== max: %d =========\n", max);
        return max;
    }

    int _DivideAndConquerGetMax(std::vector<int>& nums, int start, int end) {
        if (start == end)
            return nums[start];
 
        int mid_idx = std::floor((start + end) / 2);
        int leftMax = _DivideAndConquerGetMax(nums, start, mid_idx);
        int rightMax = _DivideAndConquerGetMax(nums, mid_idx + 1, end);
 
        // find the maximum value
        int cross = _DivideAndConquerGetCrossMax(nums, start, mid_idx, end);

        printf("mid_idx:%d, leftMax:%d, rightMax:%d, start:%d, end:%d, cross:%d\n", mid_idx, leftMax, rightMax, start, end, cross);
 
        return std::max(std::max(leftMax, rightMax), cross);
    }

    /* Use Bisection method to get the maximum number: left max and right max */
    int maxSubArrayDivideAndConquer(std::vector<int>& nums) {
        // boundary condition
        if(nums.size() <= 0) {
            return INT_MAX * (-1);
        }
        if(nums.size() == 1) {
            return nums[0];
        }
        printf("[\t");
        for(int i = 0 ; i < nums.size() ; i++)
            printf("%d\t", nums[i]);
        printf("]\n");

        // find middle index
        int mid_idx = std::floor(nums.size() / 2);
        int start = 0;
        int end = nums.size() - 1;

        printf("mid_idx:%d, start:%d, end:%d\n", mid_idx, start, end);

        return _DivideAndConquerGetMax(nums, start, end);
    }

};

int main(int argc, char *argv[]) {
    Solution *s = new Solution();

    // DP method
    printf("=== DP method ===\n");
    std::vector<int> nums1{ -2,1,-3,4,-1,2,1,-5,4 };
    printf("output1:%d\n", s -> maxSubArrayDP(nums1));

    std::vector<int> nums2{ -7,-1,-3,-4,-1,-2,-2,-5,-4 };
    printf("output2:%d\n", s -> maxSubArrayDP(nums2));

    // Divide And Conquer method
    printf("=== DivideAndConquer method ===\n");
    std::vector<int> nums3{ 4,-1,2,1,-5 };
    printf("output3:%d\n", s -> maxSubArrayDivideAndConquer(nums3));

}