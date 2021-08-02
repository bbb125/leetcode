#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <unordered_set>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/613/week-1-august-1st-august-7th/3836/
 * problem:
 * Given an array of integers nums and an integer target, return indices of the
 * two numbers such that they add up to target.
 * You may assume that each input would have exactly one solution, and you may
 * not use the same element twice. You can return the answer in any order.
 *
 * Example 1:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Output: Because nums[0] + nums[1] == 9, we return [0, 1].
 *
 * Example 2:
 * Input: nums = [3,2,4], target = 6
 * Output: [1,2]
 *
 * Example 3:
 * Input: nums = [3,3], target = 6
 * Output: [0,1]
 *
 * Constraints:
 * 2 <= nums.length <= 10^4
 * -10^9 <= nums[i] <= 10^9
 * -10^9 <= target <= 10^9
 * Only one valid answer exists.
 *
 * Follow-up: Can you come up with an algorithm that is less than O(n^2) time
 * complexity?
 */
namespace
{
class Solution
{
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        std::unordered_map<int, int> pivot(std::size(nums));

        for (int i = 0; i < static_cast<int>(std::size(nums)); ++i)
        {
            const auto num = nums[i];
            auto it = pivot.find(target - num);
            if ( it == std::end(pivot))
                pivot[num] = i;
            else
                return {it->second, i};
        }
        return {0, 0};
    }
};
}  // unnamed namespace
namespace slow_but_generic
{
class Solution
{
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        std::vector<std::reference_wrapper<int>> references{std::begin(nums),
                                                            std::end(nums)};
        std::sort(std::begin(references), std::end(references));
        auto left  = std::begin(references);
        auto right = std::end(references);
        while (left != right)
        {
            right = std::lower_bound(left, right, target - *left);
            if (*right == target - *left)
            {
                int leftIdx  = &(left->get()) - &nums.front();
                int rightIdx = &(right->get()) - &nums.front();
                return {leftIdx, rightIdx};
            }
            left = std::lower_bound(left, right - 1, target - *right);
        }
        return {};
    }
};
}  // namespace slow_but_generic
namespace
{
TEST(SolutionTests, All)
{
    std::vector<int> example3 = {3, 3};
    EXPECT_THAT(Solution{}.twoSum(example3, 6), ::testing::UnorderedElementsAre(0, 1));

    std::vector<int> example1 = {2, 7, 11, 15};
    EXPECT_THAT(Solution{}.twoSum(example1, 9), ::testing::UnorderedElementsAre(0, 1));

    std::vector<int> example2 = {3, 2, 4};
    EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));

}
}  // unnamed namespace