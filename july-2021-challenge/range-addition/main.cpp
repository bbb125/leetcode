#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
/**
 * You are given an integer length and an array updates where
 * updates[i] = [startIdxi, endIdxi, inci].
 *
 * You have an array arr of length length with all zeros, and you have some
 * operation to apply on arr. In the ith operation, you should increment all the
 * elements arr[startIdxi], arr[startIdxi + 1], ..., arr[endIdxi] by inci.
 *
 * Return arr after applying all the updates.
 *
 * Example 1:
 * Input: length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
 * Output: [-2,0,3,5,3]
 *
 * Example 2:
 * Input: length = 10, updates = [[2,4,6],[5,6,8],[1,9,-4]]
 * Output: [0,-4,2,2,2,4,4,-4,-4,-4]
 *
 *
 * Constraints:
 *
 * 1 <= length <= 105
 * 0 <= updates.length <= 104
 * 0 <= startIdxi <= endIdxi < length
 * -1000 <= inci <= 1000
 */
class Solution
{
public:
    std::vector<int> getModifiedArray(int length, std::vector<std::vector<int>>& updates)
    {
        std::vector<int> result(length);
        for (auto& update : updates)
        {
            result[update[0]] += update[2];
            if (update[1] + 1 < length)
                result[update[1] + 1] -= update[2];
        }

        int runningIncrement = 0;
        for (auto& element : result)
        {
            const int incrementChange = element;
            runningIncrement += incrementChange;
            element = runningIncrement;
        }
        return result;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    std::vector<std::vector<int>> example1{// no-format
                                           {1, 3, 2},
                                           {2, 4, 3},
                                           {0, 2, -2}};
    EXPECT_THAT(Solution{}.getModifiedArray(5, example1),
                ::testing::ElementsAre(-2, 0, 3, 5, 3));

    std::vector<std::vector<int>> example2{// no-format
                                           {2, 4, 6},
                                           {5, 6, 8},
                                           {1, 9, -4}};
    EXPECT_THAT(Solution{}.getModifiedArray(10, example2),
                ::testing::ElementsAre(0, -4, 2, 2, 2, 4, 4, -4, -4, -4));
}
}  // unnamed namespace