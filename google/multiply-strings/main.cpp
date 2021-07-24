#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <tuple>
/**
 * Given two non-negative integers num1 and num2 represented as strings, return
 * the product of num1 and num2, also represented as a string.
 *
 * Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.
 *
 *
 *
 * Example 1:
 *
 * Input: num1 = "2", num2 = "3"
 * Output: "6"
 * Example 2:
 *
 * Input: num1 = "123", num2 = "456"
 * Output: "56088"
 *
 *
 * Constraints:
 *
 * 1 <= num1.length, num2.length <= 200
 * num1 and num2 consist of digits only.
 * Both num1 and num2 do not contain any leading zero, except the number 0 itself.
 */

namespace
{
using Digit     = std::uint8_t;
using BigNumber = std::vector<Digit>;
BigNumber numberify(std::string const& str)
{
    BigNumber result;
    result.reserve(str.length());
    std::transform(std::begin(str),
                   std::end(str),
                   std::back_inserter(result),
                   [](char ch)
                   {
                       return ch - '0';
                   });
    return {std::rbegin(result), std::rend(result)};
}

BigNumber mulDigit(BigNumber bigNumber, Digit multiplier)
{
    Digit extra = 0;
    for (auto& digit : bigNumber)
    {
        auto interim = digit * multiplier + extra;
        digit        = interim % 10;
        extra        = interim / 10;
    }
    if (extra != 0)
        bigNumber.push_back(extra);
    return bigNumber;
}

BigNumber shift10(BigNumber bigNumber, std::uint8_t count)
{
    bigNumber.insert(std::begin(bigNumber), count, 0);
    return bigNumber;
}

BigNumber add(BigNumber left, BigNumber const& right)
{
    if (left.size() < right.size())
    {
        left.reserve(right.size() + 1);
        left.resize(right.size());
    }

    Digit extra = 0;
    for (std::size_t i = 0; i < left.size(); ++i)
    {
        auto rightDigit = i < right.size() ? right[i] : 0;
        auto interim    = extra + left[i] + rightDigit;
        left[i]         = interim % 10;
        extra           = interim / 10;
    }
    if (extra > 0)
        left.push_back(extra);
    return left;
}
}  // unnamed namespace
class Solution
{
public:
    std::string multiply(std::string const& str1, std::string const& str2)
    {
        auto num1 = numberify(str1);
        auto num2 = numberify(str2);
        BigNumber resultNum;

        for (std::size_t i = 0; i < num2.size(); ++i)
            resultNum = add(std::move(resultNum),  //
                            shift10(mulDigit(num1, num2[i]), i));
        std::string result;
        result.reserve(resultNum.size());
        // truncate and stringufy
        auto start = std::find_if_not(std::rbegin(resultNum), std::rend(resultNum), [](auto digit) { return digit == 0;});
        std::transform(start,
                       std::rend(resultNum),
                       std::back_inserter(result),
                       [](Digit d)
                       {
                           return d + '0';
                       });

        return result.empty() ? "0" : result;
    }
};

namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(Solution{}.multiply("2", "3"), "6");
    EXPECT_EQ(Solution{}.multiply("123", "456"), "56088");
    EXPECT_EQ(Solution{}.multiply("923939", "0"), "0");
}
}  // unnamed namespace