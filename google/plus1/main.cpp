#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
/**
 * Given a non-empty array of decimal digits representing a non-negative
 * integer, increment one to the integer.
 *
 * The digits are stored such that the most significant digit is at the head of
 * the list, and each element in the array contains a single digit.
 *
 * You may assume the integer does not contain any leading zero, except the
 * number 0 itself.
 *
 *
 *
 * Example 1:
 * Input: digits = [1,2,3]
 * Output: [1,2,4]
 * Explanation: The array represents the integer 123.
 *
 * Example 2:
 * Input: digits = [4,3,2,1]
 * Output: [4,3,2,2]
 * Explanation: The array represents the integer 4321.
 *
 * Example 3:
 * Input: digits = [0]
 * Output: [1]
 *
 *
 * Constraints:
 *
 * 1 <= digits.length <= 100
 * 0 <= digits[i] <= 9
 */

class Solution
{
public:
    std::vector<int> plusOne(std::vector<int> const& digits)
    {
        std::vector<int> result;
        result.reserve(digits.size() + 1);

        for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i)
            result.push_back(digits[i]);

        int extra = 1;
        for (auto& value : result)
        {
            value += extra;
            if (value >= 10)
            {
                extra = 1;
                value -= 10;
            }
            else
                extra = 0;

            if (extra == 0)
                break;
        }
        if (extra)
            result.push_back(extra);

        std::reverse(std::begin(result), std::end(result));
        return result;
    }
};

namespace
{
TEST(SolutionTests, All)
{
    EXPECT_THAT(Solution{}.plusOne({1, 2, 3, 4}), ::testing::ElementsAre(1, 2, 3, 5));
    EXPECT_THAT(Solution{}.plusOne({0}), ::testing::ElementsAre(1));
    EXPECT_THAT(Solution{}.plusOne({1, 2, 9, 9}), ::testing::ElementsAre(1, 3, 0, 0));
    EXPECT_THAT(Solution{}.plusOne({9, 9, 9, 9}), ::testing::ElementsAre(1, 0, 0, 0, 0));
}
}  // unnamed namespace