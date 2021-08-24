#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <complex>
#include <charconv>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/616/week-4-august-22nd-august-28th/3917/
 * problem:
 * A complex number can be represented as a string on the form "real+imaginaryi"
 * where:
 *
 * real is the real part and is an integer in the range [-100, 100].
 * imaginary is the imaginary part and is an integer in the range [-100, 100].
 * i2 == -1.
 * Given two complex numbers num1 and num2 as strings, return a string of the
 * complex number that represents their multiplications.
 *
 *
 *
 * Example 1:
 * Input: num1 = "1+1i", num2 = "1+1i"
 * Output: "0+2i"
 * Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it
 * to the form of 0+2i.
 *
 * Example 2:
 * Input: num1 = "1+-1i", num2 = "1+-1i"
 * Output: "0+-2i"
 * Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert
 * it to the form of 0+-2i.
 *
 *
 * Constraints:
 *
 * num1 and num2 are valid complex numbers.
 */
class Solution
{
public:
    using Complex = std::complex<int>;
    Complex fromString(std::string const& num)
    {
        auto separator                = num.find('+');
        Complex::value_type real      = 0;
        Complex::value_type imaginary = 0;
        std::from_chars(num.data(), num.data() + separator, real);
        std::from_chars(num.data() + separator + 1, num.data() + num.length(), imaginary);
        return {real, imaginary};
    }
    std::string toString(Complex const& complex)
    {
        return std::to_string(complex.real()) + '+' + std::to_string(complex.imag()) + 'i';
    }

    std::string complexNumberMultiply(std::string num1, std::string num2)
    {
        return toString(fromString(num1) * fromString(num2));
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ("0+2i", Solution{}.complexNumberMultiply("1+1i", "1+1i"));
    EXPECT_EQ("0+-2i", Solution{}.complexNumberMultiply("1+-1i", "1+-1i"));
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace