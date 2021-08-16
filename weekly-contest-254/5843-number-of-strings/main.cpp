#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/contest/weekly-contest-254/problems/number-of-strings-that-appear-as-substrings-in-word/
 * problem:
 * Given an array of strings patterns and a string word, return the number of
 * strings in patterns that exist as a substring in word.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 * Example 1:
 * Input: patterns = ["a","abc","bc","d"], word = "abc"
 * Output: 3
 * Explanation:
 * - "a" appears as a substring in "abc".
 * - "abc" appears as a substring in "abc".
 * - "bc" appears as a substring in "abc".
 * - "d" does not appear as a substring in "abc".
 * 3 of the strings in patterns appear as a substring in word.
 *
 * Example 2:
 * Input: patterns = ["a","b","c"], word = "aaaaabbbbb"
 * Output: 2
 * Explanation:
 * - "a" appears as a substring in "aaaaabbbbb".
 * - "b" appears as a substring in "aaaaabbbbb".
 * - "c" does not appear as a substring in "aaaaabbbbb".
 * 2 of the strings in patterns appear as a substring in word.
 *
 * Example 3:
 * Input: patterns = ["a","a","a"], word = "ab"
 * Output: 3
 * Explanation: Each of the patterns appears as a substring in word "ab".
 *
 *
 * Constraints:
 *
 * 1 <= patterns.length <= 100
 * 1 <= patterns[i].length <= 100
 * 1 <= word.length <= 100
 * patterns[i] and word consist of lowercase English letters.
 */
class Solution
{
public:
    int numOfStrings(std::vector<std::string> const& patterns, std::string word)
    {
        int result = 0;
        for (auto const& pattern : patterns)
            result += word.find(pattern) != std::string::npos;
        return result;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(3, Solution{}.numOfStrings({"a", "abc", "bc", "d"}, "abc"));
    EXPECT_EQ(2, Solution{}.numOfStrings({"a","b","c"}, "aaaaabbbbb"));
    EXPECT_EQ(3, Solution{}.numOfStrings({"a", "a", "a"}, "ab"));
}
} // unnamed namespace