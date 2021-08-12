#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <deque>
#include <stack>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3877/
 * problem:
 * Given an array of integers arr of even length, return true if and only if it
 * is possible to reorder it such that arr[2 * i + 1] = 2 * arr[2 * i] for every
 * 0 <= i < len(arr) / 2.
 *
 * Example 1:
 * Input: arr = [3,1,3,6]
 * Output: false
 *
 * Example 2:
 * Input: arr = [2,1,2,6]
 * Output: false
 *
 * Example 3:
 * Input: arr = [4,-2,2,-4]
 * Output: true
 * Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or
 * [2,4,-2,-4].
 *
 * Example 4:
 * Input: arr = [1,2,4,16,8,4]
 * Output: false
 *
 * Constraints:
 *
 * 0 <= arr.length <= 3 * 10^4
 * arr.length is even.
 * -10^5 <= arr[i] <= 10^5
 */
class Solution
{
public:
    bool canReorderDoubled(std::vector<int>& arr)
    {
        std::sort(std::begin(arr), std::end(arr));
        std::deque<int> notMatchedPositive;
        std::deque<int> notMatchedNegative;
        const int size = static_cast<int>(std::size(arr));
        for (int i = 0; i < size; ++i)
        {
            if (arr[i] < 0)
            {
                if (!notMatchedNegative.empty()
                    && arr[i] * 2 == notMatchedNegative.front())
                    notMatchedNegative.pop_front();
                else
                    notMatchedNegative.push_back(arr[i]);
            }
            else
            {
                if (!notMatchedPositive.empty() && arr[i] == notMatchedPositive.back() * 2)
                    notMatchedPositive.pop_back();
                else
                    notMatchedPositive.push_front(arr[i]);
            }

            if (static_cast<int>(std::size(notMatchedPositive) + std::size(notMatchedNegative))
                > (size - i))
                return false;
        }
        return true;
    }
};

namespace
{
TEST(SolutionTests, All)
{
    std::vector example6{-2, -6, -3, 4, -4, 2};
    EXPECT_TRUE(Solution{}.canReorderDoubled(example6));
    std::vector example5{4, 2};
    EXPECT_TRUE(Solution{}.canReorderDoubled(example5));
    std::vector example1{1, 2, 4, 16, 8, 4};
    EXPECT_FALSE(Solution{}.canReorderDoubled(example1));
    std::vector example2{4, -2, 2, -4};
    EXPECT_TRUE(Solution{}.canReorderDoubled(example2));
    std::vector example3{2, 1, 2, 6};
    EXPECT_FALSE(Solution{}.canReorderDoubled(example3));
    std::vector example4{3, 1, 3, 6};
    EXPECT_FALSE(Solution{}.canReorderDoubled(example4));
}
}  // unnamed namespace