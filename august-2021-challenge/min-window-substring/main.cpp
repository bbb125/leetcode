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
        const int sSize = static_cast<int>(std::size(s));
        std::array<int, 52> todo;
        std::unordered_map<char, std::vector<int>> tLetters;
        std::list<int> positions;
        for (int i = 0; i < sSize; ++i)
        {
            char ch = s[i];
            tLetters[ch].push_back(i);
            // find max of tops
            insert to the top of the list
            remove tLetters[ch] from list
            if ch == list first

        }
        return {};
    }
};
namespace
{
TEST(SolutionTests, All)
{
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace