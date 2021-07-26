#include <gtest/gtest.h>
#include <bitset>
#include <iostream>
/**
 * Given a positive integer n, return the number of the integers in the range
 * [0, n] whose binary representations do not contain consecutive ones.
 *
 * Example 1:
 * Input: n = 5
 * Output: 5
 * Explanation:
 * Here are the non-negative integers <= 5 with their corresponding binary
 * representations:
 * 0 : 0
 * 1 : 1
 * 2 : 10
 * 3 : 11
 * 4 : 100
 * 5 : 101
 * Among them, only integer 3 disobeys the rule (two consecutive ones) and the
 * other 5 satisfy the rule.
 *
 * Example 2:
 * Input: n = 1
 * Output: 2
 *
 * Example 3:
 * Input: n = 2
 * Output: 3
 *
 * Constraints:
 * 1 <= n <= 109
 */

class Solution
{
public:
    int findIntegers(int n)
    {
        constexpr int maxBit = 32;
        static constexpr auto fib = []
        {
            std::array<int, maxBit> result{1, 2};
            for (std::size_t i = 2; i < maxBit; ++i)
                result[i] = result[i - 1] + result[i - 2];
            return result;
        }();

        int result = 0;

        bool lasBitIsOne = false;
        std::bitset<maxBit> bits{static_cast<unsigned int>(n)};
        for (int i = maxBit - 1; i >= 0; --i)
        {
            const bool bitVal = bits.test(i);
            if (bitVal)
            {
                result += fib[i];
                if (lasBitIsOne)
                    return result;
            }
            lasBitIsOne = bitVal;
        }

        return result + 1;
    }
};

namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(5, Solution{}.findIntegers(5));
    EXPECT_EQ(2, Solution{}.findIntegers(1));
    EXPECT_EQ(3, Solution{}.findIntegers(2));
}
}  // namespace
   /**
    * 0
    * 1
    *
    * 00
    * 01
    * 10
    * 11 <--
    *
    * 000
    * 001
    * 010
    * 011
    * 100
    * 101
    * 110
    * 111
    *
    * 0000
    * 0001
    * 0010
    * 0011
    * 0100
    * 0101
    * 0110
    * 0111
    * 1000
    * 1001
    * 1010
    * 1011
    * 1100
    * 1101
    * 1110
    * 1111
    *
    * 2 ** N / 2 - ones
    * 2 ** N / 4 pairs
    * K = 2 ** N
    * K - K / 4 - (K/4 - K / 8) - (K/8 - K /16)
    * 16 - 4 - 2 - 1 = 9
    * 2 ** N - 2 ** N / 4 -
    */

// 000 000 000 001 000 010 000 011 000 100 000 101 000 110 000 111 001 000 001
// 001 001 010 001 011 001 100 001 101 001 110 001 111 010 000 010 001 010 010
// 010 011 010 100 010 101 010 110 010 111 011 000 011 001 011 010 011 011 011
// 100 011 101 011 110 011 111 100 000 100 001 100 010 100 011 100 100 100 101
// 100 110 100 111 101 000 101 001 101 010 101 011 101 100 101 101 101 110 101
// 111 110 000 110 001 110 010 110 011 110 100 110 101 110 110 110 111 111 000
// 111 001 111 010 111 011 111 100 111 101 111 110 111 111