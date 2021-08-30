#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/617/week-5-august-29th-august-31st/3956/
 * problem:
 * Given a sorted integer array nums and an integer n, add/patch elements to the
 * array such that any number in the range [1, n] inclusive can be formed by the
 * sum of some elements in the array.
 *
 * Return the minimum number of patches required.
 *
 * Example 1:
 * Input: nums = [1,3], n = 6
 * Output: 1
 * Explanation:
 * Combinations of nums are [1], [3], [1,3], which form possible sums of: 1,
 * 3, 4. Now if we add/patch 2 to nums, the combinations are: [1], [2], [3],
 * [1,3], [2,3], [1,2,3]. Possible sums are 1, 2, 3, 4, 5, 6, which now covers
 * the range [1, 6]. So we only need 1 patch.
 *
 * Example 2:
 * Input: nums = [1,5,10], n = 20
 * Output: 2
 * Explanation: The two patches can be [2, 4].
 *
 * Example 3:
 * Input: nums = [1,2,2], n = 5
 * Output: 0
 *
 * Constraints:
 * 1 <= nums.length <= 1000
 * 1 <= nums[i] <= 10^4
 * nums is sorted in ascending order.
 * 1 <= n <= 2^31 - 1
 */
class Solution
{
public:
    int minPatches(std::vector<int> const& nums, int n)
    {
        /**
         * Greedy algorithm appears to be correct.
         * If all numbers in range [1, M) are representable using some set of
         * numbers, then having an extra number K <= M we can represent
         * [1, M + K).
         * Therefore if we don't have M in our sequence we just add and assume
         * that we can represent [1, M+M).
         */
        std::int64_t currentValue = 1;
        std::size_t idx           = 0;
        int result                = 0;
        while (currentValue <= n)
        {
            if (idx < std::size(nums) && nums[idx] <= currentValue)
            {
                currentValue += nums[idx];
                ++idx;
            }
            else
            {
                currentValue += currentValue;
                ++result;
            }
        }
        return result;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(2,
        Solution{}.minPatches(
            {1, 2, 16, 19, 31, 35, 36, 64, 64, 67, 69, 71, 73, 74, 76, 79, 80, 91, 95, 96, 97},
            8));
    EXPECT_EQ(1, Solution{}.minPatches({1, 3}, 6));
    EXPECT_EQ(2, Solution{}.minPatches({1, 5, 10}, 20));
    EXPECT_EQ(0, Solution{}.minPatches({1, 2, 2}, 5));
}
}  // unnamed namespace