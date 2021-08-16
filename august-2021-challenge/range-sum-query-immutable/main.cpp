#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/615/week-3-august-15th-august-21st/3892/
 * problem:
 * Given an integer array nums, handle multiple queries of the following type:
 *
 * Calculate the sum of the elements of nums between indices left and right
 * inclusive where left <= right. Implement the NumArray class:
 *
 * NumArray(int[] nums) Initializes the object with the integer array nums.
 * int sumRange(int left, int right) Returns the sum of the elements of nums
 * between indices left and right inclusive (i.e. nums[left] + nums[left + 1] +
 * ... + nums[right]).
 *
 * Example 1:
 * Input
 * ["NumArray", "sumRange", "sumRange", "sumRange"]
 * [[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
 * Output
 * [null, 1, -1, -3]
 *
 * Explanation
 * NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
 * numArray.sumRange(0, 2); // return (-2) + 0 + 3 = 1
 * numArray.sumRange(2, 5); // return 3 + (-5) + 2 + (-1) = -1
 * numArray.sumRange(0, 5); // return (-2) + 0 + 3 + (-5) + 2 + (-1) = -3
 *
 *
 * Constraints:
 *
 * 1 <= nums.length <= 10^4
 * -10^5 <= nums[i] <= 10^5
 * 0 <= left <= right < nums.length
 * At most 104 calls will be made to sumRange.
 */
class NumArray
{
public:
    NumArray(std::vector<int> const& nums)
    {
        std::int64_t last = 0;
        partialSums_.reserve(std::size(nums) + 1);
        for (std::int64_t num : nums)
        {
            partialSums_.push_back(last);
            last += num;
        }
        partialSums_.push_back(last);
    }

    int sumRange(int left, int right)
    {
        return partialSums_[right + 1] - partialSums_[left];
    }
    std::vector<std::int64_t> partialSums_;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
namespace
{
TEST(SolutionTests, All)
{
    NumArray solution1 = std::vector{-2, 0, 3, -5, 2, -1};
    EXPECT_EQ(1, solution1.sumRange(0, 2));
    EXPECT_EQ(-1, solution1.sumRange(2, 5));
    EXPECT_EQ(-3, solution1.sumRange(0, 5));
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace