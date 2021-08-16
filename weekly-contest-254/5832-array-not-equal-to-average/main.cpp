#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <deque>
/**
 * url:
 * https://leetcode.com/contest/weekly-contest-254/problems/array-with-elements-not-equal-to-average-of-neighbors/
 * problem:
 * 1968. Array With Elements Not Equal to Average of Neighbors
 * Difficulty:Medium
 * You are given a 0-indexed array nums of distinct integers. You want to
 * rearrange the elements in the array such that every element in the rearranged
 * array is not equal to the average of its neighbors.
 *
 * More formally, the rearranged array should have the property such that for
 * every i in the range 1 <= i < nums.length - 1, (nums[i-1] + nums[i+1]) / 2 is
 * not equal to nums[i].
 *
 * Return any rearrangement of nums that meets the requirements.
 *
 * Example 1:
 * Input: nums = [1,2,3,4,5]
 * Output: [1,2,4,5,3]
 * Explanation:
 * When i=1, nums[i] = 2, and the average of its neighbors is (1+4) / 2 = 2.5.
 * When i=2, nums[i] = 4, and the average of its neighbors is (2+5) / 2 = 3.5.
 * When i=3, nums[i] = 5, and the average of its neighbors is (4+3) / 2 = 3.5.
 *
 * Example 2:
 * Input: nums = [6,2,0,9,7]
 * Output: [9,7,6,2,0]
 * Explanation:
 * When i=1, nums[i] = 7, and the average of its neighbors is (9+6) / 2 = 7.5.
 * When i=2, nums[i] = 6, and the average of its neighbors is (7+2) / 2 = 4.5.
 * When i=3, nums[i] = 2, and the average of its neighbors is (6+0) / 2 = 3.
 *
 *
 * Constraints:
 *
 * 3 <= nums.length <= 105
 * 0 <= nums[i] <= 105
 */
namespace first_guess
{
// my solution which was accepted

class Solution
{
public:
    std::vector<int> rearrangeArray(std::vector<int>& nums)
    {
        int size            = static_cast<int>(std::size(nums));
        bool requiresChange = true;
        while (requiresChange)
        {
            requiresChange = false;
            for (int i = 1; i < size - 1; ++i)
            {
                double avg = (nums[i - 1] + nums[i + 1]) / 2;
                if (nums[i] == avg)
                {
                    std::swap(nums[i], nums[i + 1]);
                    requiresChange = true;
                }
            }
        }
        return nums;
    }
};
} // namespace first_guess
/**
 * The correct solution is very similar but better.
 * 	There is a very simple approach to it as well.
 *	- Scan from left to right and fix the invalid triplets by swapping
 *	- Scan from right to left and fix the invalid triplets by swapping
 *
 * Note : If you only do the first scanning and expect it to be a valid result,
 * it's not. It is not gauranteed. Unfortunately the test cases are weak and only
 * 1 test case fails if you do first scanning only (i.e you will get 219 / 220
 * test cases passed.) Example : {0, 1, 2, 3, 4, 5} -> Only doing 1st scan will
 * fail here (See the image at the bottom to see dry run)
 */
namespace
{
TEST(SolutionTests, All)
{
    using namespace first_guess;
    using namespace ::testing;
    std::vector<int> example1 = {1, 2, 3, 4, 5};
    EXPECT_THAT(Solution{}.rearrangeArray(example1), ElementsAre(1, 2, 4, 5, 3));
    std::vector<int> example2 = {6, 2, 0, 9, 7};
    EXPECT_THAT(Solution{}.rearrangeArray(example2), ElementsAre(9, 7, 6, 2, 0));
}
} // unnamed namespace