#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <vector>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3888/
 * problem:
 * Given an m x n integer matrix matrix, if an element is 0, set its entire row
 * and column to 0's, and return the matrix.
 *
 * You must do it in place.
 *
 * Example 1:
 * Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
 * Output: [[1,0,1],[0,0,0],[1,0,1]]
 *
 * Example 2:
 * Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
 * Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 *
 * Constraints:
 *
 * m == matrix.length
 * n == matrix[0].length
 * 1 <= m, n <= 200
 * -2*31 <= matrix[i][j] <= 2*31 - 1
 *
 * Follow up:
 *
 * A straightforward solution using O(mn) space is probably a bad idea.
 * A simple improvement uses O(m + n) space, but still not the best solution.
 * Could you devise a constant space solution?
 */
class Solution
{
public:
    void setZeroes(std::vector<std::vector<int>>& matrix)
    {
        bool zeroZeroColumn = false;
        for (std::size_t i = 0; i < std::size(matrix); ++i)
        {
            if (matrix[i][0] == 0)
                zeroZeroColumn = true;

            for (std::size_t j = 1; j < std::size(matrix[i]); ++j)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        for (auto i = static_cast<int>(std::size(matrix)) - 1; i >= 0; --i)
        {
            for (auto j = static_cast<int>(std::size(matrix[i])) - 1; j >= 1; --j)
            {
                if (matrix[0][j] == 0 || matrix[i][0] == 0)
                    matrix[i][j] = 0;
            }
        }

        if (zeroZeroColumn)
        {
            for (std::size_t i = 0; i < std::size(matrix); ++i)
                matrix[i][0] = 0;
        }
    }
};
namespace
{
TEST(SolutionTests, All)
{
    using namespace ::testing;
    std::vector<std::vector<int>> example1{//
                                           {1, 1, 1},
                                           {1, 0, 1},
                                           {1, 1, 1}};
    Solution{}.setZeroes(example1);
    EXPECT_THAT(example1,     //
                ElementsAre(  //
                    ElementsAre(1, 0, 1),
                    ElementsAre(0, 0, 0),
                    ElementsAre(1, 0, 1)));

    std::vector<std::vector<int>> example2{//
                                           {0, 1, 2, 0},
                                           {3, 4, 5, 2},
                                           {1, 3, 1, 5}};
    Solution{}.setZeroes(example2);
    EXPECT_THAT(example2,     //
                ElementsAre(  //
                    ElementsAre(0, 0, 0, 0),
                    ElementsAre(0, 4, 5, 0),
                    ElementsAre(0, 3, 1, 0)));

    std::vector<std::vector<int>> example3{//
                                           {1},
                                           {0}};
    Solution{}.setZeroes(example3);
    EXPECT_THAT(example3,     //
                ElementsAre(  //
                    ElementsAre(0),
                    ElementsAre(0)));

    std::vector<std::vector<int>> example4{//
                                           {1, 2, 3, 4},
                                           {5, 0, 7, 8},
                                           {0, 10, 11, 12},
                                           {13, 14, 15, 0}};
    Solution{}.setZeroes(example4);
    EXPECT_THAT(example4,     //
                ElementsAre(  //
                    ElementsAre(0, 0, 3, 0),
                    ElementsAre(0, 0, 0, 0),
                    ElementsAre(0, 0, 0, 0),
                    ElementsAre(0, 0, 0, 0)));
}
}  // unnamed namespace