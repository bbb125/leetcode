#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

/**
 * url:
 * problem:
 */

class Solution
{
public:
    long long maxMatrixSum(std::vector<std::vector<int>>& matrix)
    {
        const int size = static_cast<int>(std::size(matrix));

        std::int64_t min    = std::abs(matrix[0][0]);
        int negativeCount   = 0;
        std::int64_t sumAbs = 0;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (std::abs(matrix[i][j]) < min)
                    min = std::abs(matrix[i][j]);
                sumAbs += std::abs(matrix[i][j]);
                if (matrix[i][j] < 0)
                    ++negativeCount;
            }
        }
        return sumAbs - ((negativeCount % 2 == 0) ? 0 : 2 * min);
    }
};
namespace
{
TEST(SolutionTests, All)
{
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace