#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/617/week-5-august-29th-august-31st/3958/
 * problem:
 * Suppose an array of length n sorted in ascending order is rotated between 1
 * and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:
 *
 * [4,5,6,7,0,1,2] if it was rotated 4 times.
 * [0,1,2,4,5,6,7] if it was rotated 7 times.
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results
 * in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
 *
 * Given the sorted rotated array nums of unique elements, return the minimum
 * element of this array.
 *
 * You must write an algorithm that runs in O(log n) time.
 *
 * Example 1:
 * Input: nums = [3,4,5,1,2]
 * Output: 1
 * Explanation: The original array was [1,2,3,4,5] rotated 3 times.
 *
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2]
 * Output: 0
 * Explanation: The original array was [0,1,2,4,5,6,7] and it was rotated 4
 * times.
 *
 * Example 3:
 * Input: nums = [11,13,15,17]
 * Output: 11
 * Explanation: The original array was [11,13,15,17] and it was rotated 4 times.
 *
 * Constraints:
 * n == nums.length
 * 1 <= n <= 5000
 * -5000 <= nums[i] <= 5000
 * All the integers of nums are unique.
 * nums is sorted and rotated between 1 and n times.
 */
namespace logn
{
class Solution
{
public:
    int findMin(std::vector<int> const& nums)
    {
        int left  = 0;
        int right = static_cast<int>(std::size(nums)) - 1;
        while (right > left)
        {
            if (nums[left] <= nums[right])
                return nums[left];

            int mid = (left + right) / 2;

            if (nums[left] > nums[mid])
                right = mid;
            else
                left = mid + 1;
        }
        return nums[left];
    }
};
}  // namespace logn
namespace
{
TEST(SolutionTests, All)
{
    using namespace logn;
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
    EXPECT_EQ(0, Solution{}.findMin({0, 1, 6, 7, 8, 9}));
    EXPECT_EQ(1, Solution{}.findMin({3, 4, 5, 1, 2}));
    EXPECT_EQ(0, Solution{}.findMin({4, 5, 6, 7, 0, 1, 2}));
    EXPECT_EQ(11, Solution{}.findMin({11, 13, 15, 17}));
}
}  // unnamed namespace