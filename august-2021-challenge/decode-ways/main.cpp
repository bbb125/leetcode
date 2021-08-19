#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/615/week-3-august-15th-august-21st/3902/
 * problem:
 * A message containing letters from A-Z can be encoded into numbers using the
 * following mapping:
 *
 * 'A' -> "1"
 * 'B' -> "2"
 * ...
 * 'Z' -> "26"
 * To decode an encoded message, all the digits must be grouped then mapped back
 * into letters using the reverse of the mapping above (there may be multiple
 * ways). For example, "11106" can be mapped into:
 *
 * "AAJF" with the grouping (1 1 10 6)
 * "KJF" with the grouping (11 10 6)
 * Note that the grouping (1 11 06) is invalid because "06" cannot be mapped
 * into 'F' since "6" is different from "06".
 *
 * Given a string s containing only digits, return the number of ways to decode
 * it.
 *
 * The answer is guaranteed to fit in a 32-bit integer.
 *
 * Example 1:
 * Input: s = "12"
 * Output: 2
 * Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).
 *
 * Example 2:
 * Input: s = "226"
 * Output: 3
 * Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2
 * 2 6).
 *
 * Example 3:
 * Input: s = "0"
 * Output: 0
 * Explanation: There is no character that is mapped to a number starting with
 * 0. The only valid mappings with 0 are 'J' -> "10" and 'T' -> "20", neither of
 * which start with 0. Hence, there are no valid ways to decode this since all
 * digits need to be mapped.
 *
 * Example 4:
 * Input: s = "06"
 * Output: 0
 * Explanation: "06" cannot be mapped to "F" because of the leading zero ("6" is
 * different from "06").
 *
 *
 * Constraints:
 * 1 <= s.length <= 100
 * s contains only digits and may contain leading zero(s).
 */
class Solution
{
public:
    int numDecodings(std::string s)
    {
        const int sSize = static_cast<int>(std::size(s));
        int last1       = 1;
        int last2       = 1;

        for (int i = 0; i < sSize; ++i)
        {
            int next = 0;
            if (s[i] != '0')
                next += last1;

            if (i >= 1 && s[i - 1] > '0')
            {
                int number = ((s[i - 1] - '0') * 10 + s[i] - '0');
                if (number > 0 && number <= 26)
                    next += last2;
            }
            last2 = last1;
            last1 = next;
        }
        return last1;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(3, Solution{}.numDecodings("226"));
    EXPECT_EQ(2, Solution{}.numDecodings("12"));

    EXPECT_EQ(0, Solution{}.numDecodings("0"));
    EXPECT_EQ(0, Solution{}.numDecodings("06"));
}
}  // unnamed namespace