#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url: https://leetcode.com/contest/weekly-contest-255/problems/find-unique-binary-string/
 * problem:
 * Given an array of strings nums containing n unique binary strings each of length
 * n, return a binary string of length n that does not appear in nums. If there
 * are multiple answers, you may return any of them.
 *
 *
 *
 * Example 1:
 *
 * Input: nums = ["01","10"]
 * Output: "11"
 * Explanation: "11" does not appear in nums. "00" would also be correct.
 *
 *
 * Example 2:
 * Input: nums = ["00","01"]
 * Output: "11"
 * Explanation: "11" does not appear in nums. "10" would also be correct.
 *
 *
 * Example 3:
 * Input: nums = ["111","011","001"]
 * Output: "101"
 * Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct.
 *
 *
 * Constraints:
 *
 * n == nums.length
 * 1 <= n <= 16
 * nums[i].length == n
 * nums[i] is either '0' or '1'.
 */
class Solution
{
public:
    std::string findDifferentBinaryString(std::vector<std::string> const& nums)
    {
        std::vector<std::uint16_t> nums_;
        for (auto const& num : nums)
        {
            std::uint16_t result = 0;
            for (auto ch: num)
            {
                result *= 2;
                result += ch - '0';
            }
            nums_.push_back(result);
        }
        std::sort(std::begin(nums_), std::end(nums_));
        auto last = std::unique(std::begin(nums_), std::end(nums_));
        nums_.erase(last, std::end(nums_));
        std::size_t idx = 0;
        for (std::uint16_t i = nums_.front();; ++i)
        {
            if (idx < std::size(nums_) && i == nums_[idx])
                ++idx;
            else
            {
                std::string result;
                for (std::size_t k = 0; k < std::size(nums.front()); ++k)
                {
                    result.push_back(i % 2 + '0');
                    i /= 2;
                }
                std::reverse(std::begin(result), std::end(result));
                return result;
            }
        }
        return {};
    }
};
namespace
{
TEST(SolutionTests, All)
{
    using namespace std::string_literals;
    EXPECT_EQ("11", Solution{}.findDifferentBinaryString({"00"s, "01"s}));
    EXPECT_EQ("11", Solution{}.findDifferentBinaryString({"01"s, "10"s}));

    EXPECT_EQ("101", Solution{}.findDifferentBinaryString({"111"s, "011"s, "001"s}));
}
}  // unnamed namespace