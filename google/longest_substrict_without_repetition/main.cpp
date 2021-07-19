#include <gtest/gtest.h>

#include <string>
#include <array>
/**
 * Given a string s, find the length of the longest substring without repeating
 * characters.
 *
 * Example 1:
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 *
 * Example 2:
 * Input: s = "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 *
 * Example 3:
 * Input: s = "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 * Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 *
 * Example 4:
 * Input: s = ""
 * Output: 0
 *
 *
 * Constraints:
 *
 * 0 <= s.length <= 5 * 104
 * s consists of English letters, digits, symbols and spaces.
 */
class Solution
{
public:
    int lengthOfLongestSubstring(std::string s)
    {
        const int stringLength         = static_cast<int>(s.length());
        std::array<int, 256> positions = {};
        positions.fill(-1);

        int maxLength     = 0;
        int currentLength = 0;

        for (int i = 0; i < stringLength; ++i)
        {
            int& previousOccurrence = positions[s[i]];
            if (previousOccurrence == -1 || previousOccurrence < ( i - currentLength ))
            {
                ++currentLength;
            }
            else
            {
                maxLength          = std::max(currentLength, maxLength);
                currentLength      = i - previousOccurrence;
            }
            previousOccurrence = i;
        }
        maxLength = std::max(currentLength, maxLength);
        return maxLength;
    }
};


namespace
{
TEST(SolutionTests, All)
{
    /**
     * Example 1:
     * Input: s = "abcabcbb"
     * Output: 3
     * Explanation: The answer is "abc", with the length of 3.
     */
    EXPECT_EQ(3, Solution{}.lengthOfLongestSubstring("abcabcbb"));
    /**
     * Example 2:
     * Input: s = "bbbbb"
     * Output: 1
     * Explanation: The answer is "b", with the length of 1.
     */
    EXPECT_EQ(1, Solution{}.lengthOfLongestSubstring("bbbbb"));
    /**
     * Example 3:
     * Input: s = "pwwkew"
     * Output: 3
     * Explanation: The answer is "wke", with the length of 3.
     * Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
     */
    EXPECT_EQ(3, Solution{}.lengthOfLongestSubstring("pwwkew"));
    /**
     * Example 4:
     * Input: s = ""
     * Output: 0
     */
    EXPECT_EQ(0, Solution{}.lengthOfLongestSubstring(""));

    /**
     * extra tests
     */
    EXPECT_EQ(1, Solution{}.lengthOfLongestSubstring("aa"));
    EXPECT_EQ(2, Solution{}.lengthOfLongestSubstring("abba"));
    EXPECT_EQ(1, Solution{}.lengthOfLongestSubstring(" "));
}
}  // namespace
