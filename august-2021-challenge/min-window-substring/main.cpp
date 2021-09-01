#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <list>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/615/week-3-august-15th-august-21st/3891/
 * problem:
 * Given two strings s and t of lengths m and n respectively, return the minimum
 * window substring of s such that every character in t (including duplicates)
 * is included in the window. If there is no such substring, return the empty
 * string "".
 *
 * The testcases will be generated such that the answer is unique.
 *
 * A substring is a contiguous sequence of characters within the string.
 *
 * Example 1:
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 * Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C'
 * from string t.
 *
 * Example 2:
 * Input: s = "a", t = "a"
 * Output: "a"
 * Explanation: The entire string s is the minimum window.
 *
 * Example 3:
 * Input: s = "a", t = "aa"
 * Output: ""
 * Explanation: Both 'a's from t must be included in the window.
 * Since the largest window of s only has one 'a', return empty string.
 *
 *
 * Constraints:
 *
 * m == s.length
 * n == t.length
 * 1 <= m, n <= 10^5
 * s and t consist of uppercase and lowercase English letters.
 *
 *
 * Follow up: Could you find an algorithm that runs in O(m + n) time?
 */
class Solution
{
public:
    std::string minWindow(std::string s, std::string t)
    {
        auto pattern = [&]
        {
            std::unordered_map<char, int> result;
            for (auto ch : t)
                result[ch] += 1;
            return result;
        }();
        std::unordered_map<char, int> occurrences;

        std::size_t left            = 0;
        std::size_t right           = 0;
        std::size_t numberOfMatched = 0;
        std::string_view result;
        bool foundAny = false;
        while (right != std::size(s) || numberOfMatched == std::size(pattern))
        {
            if (numberOfMatched != std::size(pattern))
            {
                auto ch = s[right++];
                if (!pattern.count(ch))
                    continue;

                ++occurrences[ch];
                numberOfMatched += (occurrences[ch] == pattern[ch]);
            }
            else
            {
                if (!foundAny || std::size(result) > (right - left))
                {
                    result = std::string_view{s.data() + left, right - left};
                    foundAny = true;
                }

                auto ch = s[left++];
                if (!pattern.count(ch))
                    continue;

                --occurrences[ch];
                numberOfMatched -= (occurrences[ch] < pattern[ch]);
            }
        }
        return foundAny ? std::string{result} : std::string{};
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ("cwae", Solution{}.minWindow("cabwefgewcwaefgcf", "cae"));
    EXPECT_EQ("BANC", Solution{}.minWindow("ADOBECODEBANC", "ABC"));
    EXPECT_EQ("a", Solution{}.minWindow("a", "a"));
    EXPECT_EQ("", Solution{}.minWindow("a", "aa"));
}
}  // unnamed namespace