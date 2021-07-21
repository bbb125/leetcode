#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

/**
 * https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/610/week-3-july-15th-july-21st/3817/
 *
 * You are given an array arr which consists of only zeros and ones,
 * divide the array into three non-empty parts such that all of these
 * parts represent the same binary value.
 *
 * If it is possible, return any [i, j] with i + 1 < j, such that:
 *
 * arr[0], arr[1], ..., arr[i] is the first part,
 *         arr[i + 1], arr[i + 2], ..., arr[j - 1] is the second part, and
 *         arr[j], arr[j + 1], ..., arr[arr.length - 1] is the third part.
 * All three parts have equal binary values.
 * If it is not possible, return [-1, -1].
 *
 * Note that the entire part is used when considering what binary value it
 * represents. For example, [1,1,0] represents 6 in decimal, not 3. Also,
 * leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.
 *
 * Example 1:
 *
 * Input: arr = [1,0,1,0,1]
 * Output: [0,3]
 * Example 2:
 *
 * Input: arr = [1,1,0,1,1]
 * Output: [-1,-1]
 * Example 3:
 *
 * Input: arr = [1,1,0,0,1]
 * Output: [0,2]
 *
 *
 * Constraints:
 *
 * 3 <= arr.length <= 3 * 104
 * arr[i] is 0 or 1
 */
class Solution
{
public:
    std::vector<int> threeEqualParts(std::vector<int> const& arr)
    {
        // every segment must have equal number of ones, so let's remember their
        // positions
        std::vector<int> ones;
        ones.reserve(arr.size());
        for (std::size_t i = 0; i < arr.size(); ++i)
            if (arr[i] == 1)
                ones.push_back(i);

        const int onesSize = static_cast<int>(ones.size());
        const int arrSize = static_cast<int>(arr.size());
        if (onesSize == 0)
            return {0, arrSize - 1};

        if (onesSize % 3 != 0)
            return {-1, -1};
        int start1 = ones[0];
        int start2 = ones[onesSize / 3];
        int start3 = ones[(onesSize / 3) * 2];
        while (start3 < arrSize)
        {
            if (arr[start1] != arr[start2] || arr[start2] != arr[start3])
                return {-1, -1};
            ++start1;
            ++start2;
            ++start3;
        }

        return {start1 - 1, start2};
    }
};

namespace
{
TEST(SolutionTests, All)
{
    // basic
    EXPECT_THAT(Solution{}.threeEqualParts({1, 0, 1, 0, 1}), ::testing::ElementsAre(0, 3));
    EXPECT_THAT(Solution{}.threeEqualParts({1, 1, 0, 1, 1}),
                ::testing::ElementsAre(-1, -1));
    EXPECT_THAT(Solution{}.threeEqualParts({1, 1, 0, 0, 1}), ::testing::ElementsAre(0, 2));

    // extra
    EXPECT_THAT(Solution{}.threeEqualParts({1, 0, 1, 1, 0}),
                ::testing::ElementsAre(-1, -1));
    EXPECT_THAT(Solution{}.threeEqualParts({0, 0, 0, 0, 0}), ::testing::ElementsAre(0, 4));
}
}  // namespace
