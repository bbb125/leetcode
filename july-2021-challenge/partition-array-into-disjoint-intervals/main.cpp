#include <gtest/gtest.h>

#include <limits>
#include <vector>
/**
 * Given an array nums, partition it into two (contiguous) subarrays left and
 * right so that:
 *
 * Every element in left is less than or equal to every element in right.
 * left and right are non-empty.
 * left has the smallest possible size.
 * Return the length of left after such a partitioning.  It is guaranteed that
 * such a partitioning exists.
 *
 *
 *
 * Example 1:
 * Input: nums = [5,0,3,8,6]
 * Output: 3
 * Explanation: left = [5,0,3], right = [8,6]
 *
 * Example 2:
 * Input: nums = [1,1,1,0,6,12]
 * Output: 4
 * Explanation: left = [1,1,1,0], right = [6,12]
 *
 *
 * Note:
 *
 * 2 <= nums.length <= 30000
 * 0 <= nums[i] <= 106
 * It is guaranteed there is at least one way to partition nums as described.
 */
class Solution
{
public:
    int partitionDisjoint(std::vector<int> const& nums)
    {
        const int numsSize = std::ssize(size);
        std::vector<int> minNums(numsSize + 1, std::numeric_limits<int>::max());
        for (int i = numsSize - 1; i >= 0; --i)
            minNums[i] = std::min(nums[i], minNums[i + 1]);

        int currentMax = 0;
        for (int i = 0; i < numsSize; ++i)
        {
            currentMax = std::max(currentMax, nums[i]);
            if (currentMax <= minNums[i + 1])
                return i + 1;
        }
        return numsSize - 1;  // never happens
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(Solution{}.partitionDisjoint({5, 0, 3, 8, 6}), 3);
    EXPECT_EQ(Solution{}.partitionDisjoint({1, 1, 1, 0, 6, 12}), 4);
    EXPECT_EQ(Solution{}.partitionDisjoint({1, 1}), 1);
}
}  // unnamed namespace