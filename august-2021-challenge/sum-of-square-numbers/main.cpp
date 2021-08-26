#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/616/week-4-august-22nd-august-28th/3918/
 * problem:
 * Given a non-negative integer c, decide whether there're two integers a and b
 * such that a2 + b2 = c.
 *
 * Example 1:
 * Input: c = 5
 * Output: true
 * Explanation: 1 * 1 + 2 * 2 = 5
 *
 * Example 2:
 * Input: c = 3
 * Output: false
 *
 * Example 3:
 * Input: c = 4
 * Output: true
 *
 * Example 4:
 * Input: c = 2
 * Output: true
 *
 * Example 5:
 * Input: c = 1
 * Output: true
 *
 * Constraints:
 *
 * 0 <= c <= 2**31 - 1
 */
class Solution
{
public:
    bool judgeSquareSum(int c)
    {
        int cRoot = std::floor(std::sqrt(c));
        for (int a = 0; a <= cRoot; ++a)
        {
            int aSquare = a * a;
            int bSquare = c - aSquare;
            int b       = std::sqrt(bSquare);
            if (b * b == bSquare)
                return true;
        }
        return false;
    }
};namespace
{
TEST(SolutionTests, All)
{
    EXPECT_TRUE(Solution{}.judgeSquareSum(5));
    EXPECT_FALSE(Solution{}.judgeSquareSum(3));
    EXPECT_TRUE(Solution{}.judgeSquareSum(4));
    EXPECT_TRUE(Solution{}.judgeSquareSum(2));
    EXPECT_TRUE(Solution{}.judgeSquareSum(1));
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace