#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3875/
 * problem:
 * Given two non-negative integers, num1 and num2 represented as string, return
 * the sum of num1 and num2 as a string.
 *
 * You must solve the problem without using any built-in library for handling
 * large integers (such as BigInteger). You must also not convert the inputs to
 * integers directly.
 *
 *
 * Example 1:
 * Input: num1 = "11", num2 = "123"
 * Output: "134"
 *
 * Example 2:
 * Input: num1 = "456", num2 = "77"
 * Output: "533"
 *
 * Example 3:
 * Input: num1 = "0", num2 = "0"
 * Output: "0"
 *
 *
 * Constraints:
 *
 * 1 <= num1.length, num2.length <= 104
 * num1 and num2 consist of only digits.
 * num1 and num2 don't have any leading zeros except for the zero itself.
 */
class Solution
{
public:
    std::string addStrings(std::string num1, std::string num2)
    {
        auto it1  = std::rbegin(num1);
        auto end1 = std::rend(num1);
        auto it2  = std::rbegin(num2);
        auto end2 = std::rend(num2);
        int extra = 0;
        std::string result;
        result.reserve(std::max(std::size(num1), std::size(num2)) + 2);
        for (; !(it1 == end1 && it2 == end2);)
        {
            int n1  = it1 != end1 ? *(it1++) - '0' : 0;
            int n2  = it2 != end2 ? *(it2++) - '0' : 0;
            int sum = extra + n1 + n2;
            extra   = sum / 10;
            result.push_back(sum - extra * 10 + '0');
        }
        if (extra)
            result.push_back(extra + '0');
        std::reverse(std::begin(result), std::end(result));
        return result;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ("134", Solution{}.addStrings("11", "123"));
    EXPECT_EQ("533", Solution{}.addStrings("456", "77"));
    EXPECT_EQ("0", Solution{}.addStrings("0", "0"));
}
}  // unnamed namespace