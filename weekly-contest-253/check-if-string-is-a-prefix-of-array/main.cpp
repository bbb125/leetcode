#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
/**
 * url: https://leetcode.com/contest/weekly-contest-253/problems/check-if-string-is-a-prefix-of-array/
 * problem:
 * Given a string s and an array of strings words, determine whether s is a
 * prefix string of words.
 *
 * A string s is a prefix string of words if s can be made by concatenating the
 * first k strings in words for some positive k no larger than words.length.
 *
 * Return true if s is a prefix string of words, or false otherwise.
 *
 *
 * Example 1:
 * Input: s = "iloveleetcode", words = ["i","love","leetcode","apples"]
 * Output: true
 * Explanation:
 * s can be made by concatenating "i", "love", and "leetcode" together.
 *
 * Example 2:
 * Input: s = "iloveleetcode", words = ["apples","i","love","leetcode"]
 * Output: false
 * Explanation:
 * It is impossible to make s using a prefix of arr.
 *
 *
 * Constraints:
 *
 * 1 <= words.length <= 100
 * 1 <= words[i].length <= 20
 * 1 <= s.length <= 1000
 * words[i] and s consist of only lowercase English letters.
 */

class Solution
{
public:
    bool isPrefixString(std::string s, std::vector<std::string> const& words)
    {
        int i = 0;
        for (auto const& word : words)
        {
            for (char ch : word)
            {
                if (i == static_cast<int>(std::size(s)))
                    return false;
                if (s[i] != ch)
                    return false;
                ++i;
            }
            if (i == static_cast<int>(std::size(s)))
                return true;
            ;
        }

        return i == static_cast<int>(std::size(s));
    }
};
namespace
{
TEST(SolutionTests, All)
{
    //    Input: s = "iloveleetcode", words = ["apples","i","love","leetcode"]
    //        Output: false
    //        Explanation:
    EXPECT_FALSE(Solution{}.isPrefixString("iloveleetcode",
                                           {"apples", "i", "love", "leetcode"}));
    // Input: s = "iloveleetcode", words = ["i","love","leetcode","apples"]
    //     Output: true
    //     Explanation:
    //     s can be made by concatenating "i", "love", and "leetcode" together.
    EXPECT_TRUE(Solution{}.isPrefixString("iloveleetcode",
                                          {"i", "love", "leetcode", "apples"}));
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
    //    "a"
    //    ["aa","aaaa","banana"]
    EXPECT_FALSE(Solution{}.isPrefixString("a", {"aa", "aaaa", "banana"}));
    EXPECT_TRUE(Solution{}.isPrefixString("aa", {"aa", "aaaa", "banana"}));
    EXPECT_TRUE(Solution{}.isPrefixString("aa", {"aa"}));
    EXPECT_FALSE(Solution{}.isPrefixString("aaa", {"aa"}));
}
}  // unnamed namespace