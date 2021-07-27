//
// Created by vladimir on 7/27/21.
//
#include <gtest/gtest.h>

#include <vector>
#include <unordered_map>

/**
 * Given an array nums of n integers and an integer target, find three integers
 * in nums such that the sum is closest to target. Return the sum of the three
 * integers. You may assume that each input would have exactly one solution.
 *
 * Example 1:
 * Input: nums = [-1,2,1,-4], target = 1
 * Output: 2
 * Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 *
 *
 * Constraints:
 *
 * 3 <= nums.length <= 10^3
 * -10^3 <= nums[i] <= 10^3
 * -10^4 <= target <= 10^4
 */
class Solution
{
public:
    int threeSumClosest(std::vector<int> const& _nums, int target)
    {
        auto nums = _nums;
        std::sort(std::begin(nums), std::end(nums));
        const int size = std::ssize(nums);

        int closestSum = std::numeric_limits<int>::max();

        for (int i = 0; i < size - 1; ++i)
        {
            auto first     = nums[i];
            auto secondIdx = i + 1;
            auto thirdIdx  = size - 1;
            if (i > 0 && first == nums[i - 1])
                continue;
            while (secondIdx < thirdIdx)
            {
                auto second      = nums[secondIdx];
                const auto third = nums[thirdIdx];
                const auto sum   = first + second + third;
                if (closestSum == std::numeric_limits<int>::max()
                    || std::abs(sum - target) < std::abs(closestSum - target))
                    closestSum = sum;

                if (sum < target)
                    ++secondIdx;
                else if (sum > target)
                    --thirdIdx;
                else
                    return closestSum;
            }
        }
        return closestSum;
    }
};

namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(Solution{}.threeSumClosest({-1, 2, 1, -4}, 1), 2);
    EXPECT_EQ(Solution{}.threeSumClosest({0, 1, 2}, 3), 3);
    EXPECT_EQ(Solution{}.threeSumClosest({1, 1, 1, 1}, -100), 3);
}
}  // namespace