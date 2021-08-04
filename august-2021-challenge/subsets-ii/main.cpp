#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <bitset>
#include <unordered_set>
#include <stack>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/613/week-1-august-1st-august-7th/3837/
 * problem:
 * Given an integer array nums that may contain duplicates, return all possible
 * subsets (the power set).
 *
 * The solution set must not contain duplicate subsets. Return the solution in
 * any order.
 *
 * Example 1:
 * Input: nums = [1,2,2]
 * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 *
 * Example 2:
 * Input: nums = [0]
 * Output: [[],[0]]
 *
 * Constraints:
 * 1 <= nums.length <= 10
 * -10 <= nums[i] <= 10
 */
namespace little_slower
{
class Solution
{
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums)
    {
        std::sort(std::begin(nums), std::end(nums));

        const int size            = static_cast<int>(std::size(nums));
        const int maxCombinations = 1 << (size);

        std::unordered_set<std::uint64_t> seen(maxCombinations);
        using Number = std::vector<int>;
        std::vector<Number> result;
        result.reserve(maxCombinations);
        for (int i = 0; i < maxCombinations; ++i)
        {
            std::uint32_t mask = 1;

            Number v;
            v.reserve(size);
            std::uint64_t number = 0;
            std::uint64_t base   = 1;
            for (int j = 0; j < size; ++j)
            {
                if ((i & mask) != 0)
                {
                    v.push_back(nums[j]);
                    number += ((nums[j] + 11) * base);
                    base *= 21;
                }
                mask <<= 1;
            }
            if (!seen.count(number))
            {
                result.push_back(std::move(v));
                seen.insert(number);
            }
        }
        return result;
    }
};
}  // namespace little_slower
namespace fast
{
//class Solution
//{
//public:
//    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums)
//    {
//        std::vector<vector<int>> subsets;
//        std::vector<int> currentSubset;
//        std::sort(nums.begin(), nums.end());
//
//        subsetsWithDupHelper(subsets, currentSubset, nums, 0);
//        return subsets;
//    }
//
//private:
//    void subsetsWithDupHelper(std::vector<std::vector<int>>& subsets,
//                              std::vector<int>& currentSubset,
//                              std::vector<int>& nums,
//                              int index)
//    {
//        // Add the subset formed so far to the subsets list.
//        subsets.push_back(currentSubset);
//        std::stack<int> indexes;
//        indexes.push(index);
//        while(true)
//        {
//            int i = indexes.top();
//            if (i == nums.size())
//            {
//                i = indexes.top();
//                indexes.pop();
//            }
//            // If the current element is a duplicate, ignore.
//            if (i != index && nums[i] == nums[i - 1])
//            {
//                ++i;
//                continue;
//            }
//            currentSubset.push_back(nums[i]);
//            indexes.push(i);
//            subsetsWithDupHelper(subsets, currentSubset, nums, i + 1);
//            currentSubset.pop_back();
//            ++i;
//        }
//    }
//};
}  // namespace fast
namespace
{
TEST(SolutionTests, All)
{
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
    std::vector<int> example2{0};
    EXPECT_THAT(Solution{}.subsetsWithDup(example2).size(), 2);
    std::vector<int> example1{1, 2, 2};
    EXPECT_THAT(Solution{}.subsetsWithDup(example1).size(), 6);
    //* Input: nums = [1,2,2]
    //        * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
}
}  // unnamed namespace