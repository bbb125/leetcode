#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3873/
 * problem:
 * You are painting a fence of n posts with k different colors. You must paint
 * the posts following these rules:
 *
 * Every post must be painted exactly one color.
 * There cannot be three or more consecutive posts with the same color.
 * Given the two integers n and k, return the number of ways you can paint the
 * fence.
 *
 * Example 1:
 * Input: n = 3, k = 2
 * Output: 6
 * Explanation: All the possibilities are shown.
 * Note that painting all the posts red or all the posts green is invalid
 * because there cannot be three posts in a row with the same color.
 *
 * Example 2:
 * Input: n = 1, k = 1
 * Output: 1
 *
 * Example 3:
 * Input: n = 7, k = 2
 * Output: 42
 *
 *
 * Constraints:
 * 1 <= n <= 50
 * 1 <= k <= 10^5
 * The testcases are generated such that the answer is in the range [0, 231 - 1]
 * for the given n and k.
 */

class Solution
{
public:
    int numWays(int n, int k)
    {
        int one = 1;
        int two = 1;
        for (int i = 1; i < n; ++i)
        {
            int newOne = two * (k - 1);
            two        = one + two * (k - 1);
            one        = newOne;
        }
        return k * two;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(9, Solution{}.numWays(2, 3));
    EXPECT_EQ(6, Solution{}.numWays(3, 2));
    EXPECT_EQ(42, Solution{}.numWays(7, 2));
    EXPECT_EQ(1, Solution{}.numWays(1, 1));
    EXPECT_EQ(1, Solution{}.numWays(2, 1));
    EXPECT_EQ(5, Solution{}.numWays(1, 5));
}
}  // unnamed namespace