#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3876/
 * problem:
 * A binary string is monotone increasing if it consists of some number of 0's
 * (possibly none), followed by some number of 1's (also possibly none).
 * You are given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0.
 * Return the minimum number of flips to make s monotone increasing.
 *
 * Example 1:
 * Input: s = "00110"
 * Output: 1
 * Explanation: We flip the last digit to get 00111.
 *
 * Example 2:
 * Input: s = "010110"
 * Output: 2
 * Explanation: We flip to get 011111, or alternatively 000111.
 *
 * Example 3:
 * Input: s = "00011000"
 * Output: 2
 * Explanation: We flip to get 00000000.
 *
 *
 * Constraints:
 * 1 <= s.length <= 10^5
 * s[i] is either '0' or '1'.
 */

namespace two_pass
{
class Solution
{
public:
    int minFlipsMonoIncr(std::string s)
    {
        std::array<std::vector<int>, 2> counts{};
        int count0 = 0;
        int count1 = 0;

        for (auto ch : s)
        {
            counts[0].push_back(count0);
            counts[1].push_back(count1);
            (ch == '0' ? count0 : count1) += 1;
        }
        counts[0].push_back(count0);
        counts[1].push_back(count1);

        const int size = static_cast<int>(std::size(s));
        int minFlips   = size;
        for (int i = 0; i <= static_cast<int>(std::size(s)); ++i)
        {
            int flips = (count0 - counts[0][i]) + counts[1][i];
            minFlips  = std::min(minFlips, flips);
        }
        return minFlips;
    }
};

}  // namespace two_pass
namespace one_pass
{
class Solution
{
public:
    int minFlipsMonoIncr(std::string s)
    {
        int count0     = 0;
        int count1     = 0;
        const int size = static_cast<int>(std::size(s));
        int minFlips   = size;
        for (auto ch : s)
        {
            int flips = count1 - count0;
            minFlips  = std::min(minFlips, flips);
            (ch == '0' ? count0 : count1) += 1;
        }
        minFlips = std::min(minFlips, count1 - count0);
        return minFlips + count0;
    }
};
}  //  namespace one_pass
namespace
{
TEST(SolutionTests, All)
{
    using namespace one_pass;
    EXPECT_EQ(2, Solution{}.minFlipsMonoIncr("00011000"));
    EXPECT_EQ(1, Solution{}.minFlipsMonoIncr("00110"));
    EXPECT_EQ(2, Solution{}.minFlipsMonoIncr("010110"));
}
}  // unnamed namespace