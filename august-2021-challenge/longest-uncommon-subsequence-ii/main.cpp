#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <string>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/616/week-4-august-22nd-august-28th/3921/
 * problem:
 * Given an array of strings strs, return the length of the longest uncommon
 * subsequence between them. If the longest uncommon subsequence does not exist,
 * return -1.
 *
 * An uncommon subsequence between an array of strings is a string that is a
 * subsequence of one string but not the others.
 *
 * A subsequence of a string s is a string that can be obtained after deleting
 * any number of characters from s.
 *
 * For example, "abc" is a subsequence of "aebdc" because you can delete the
 * underlined characters in "aebdc" to get "abc". Other subsequences of "aebdc"
 * include "aebdc", "aeb", and "" (empty string).
 *
 * Example 1:
 * Input: strs = ["aba","cdc","eae"]
 * Output: 3
 *
 * Example 2:
 * Input: strs = ["aaa","aaa","aa"]
 * Output: -1
 *
 * Constraints:
 *
 * 1 <= strs.length <= 50
 * 1 <= strs[i].length <= 10
 * strs[i] consists of lowercase English letters.
 */
namespace
{
bool isSubsequence(std::string const& left, std::string const& right)
{
    std::size_t leftIdx  = 0;
    std::size_t rightIdx = 0;
    while (leftIdx < std::size(left) && rightIdx < std::size(right))
    {
        if (left[leftIdx] == right[rightIdx])
            ++leftIdx;
        ++rightIdx;
    }
    return leftIdx == std::size(left);
}
}  // unnamed namespace
class Solution
{
public:
    int findLUSlength(std::vector<std::string> const& strs)
    {
        int max = -1;
        for (std::size_t i = 0; i < std::size(strs); ++i)
        {
            auto subsequenceOfAny = [i, strs]()
            {
                for (std::size_t j = 0; j < std::size(strs); ++j)
                {
                    if (j == i)
                        continue;
                    if (isSubsequence(strs[i], strs[j]))
                        return true;
                }
                return false;
            };
            if (!subsequenceOfAny())
                max = std::max(static_cast<int>(std::size(strs[i])), max);
        }
        return max;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(3, Solution{}.findLUSlength({"aba", "cdc", "eae"}));
    EXPECT_EQ(-1, Solution{}.findLUSlength({"aaa", "aaa", "aa"}));
}
}  // unnamed namespace