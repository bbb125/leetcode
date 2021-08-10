#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stack>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3874/
 * problem:
 * Given an m x n matrix, return a new matrix answer where answer[row][col] is
 * the rank of matrix[row][col].
 *
 * The rank is an integer that represents how large an element is compared to
 * other elements. It is calculated using the following rules:
 *
 * The rank is an integer starting from 1.
 * If two elements p and q are in the same row or column, then:
 * If p < q then rank(p) < rank(q)
 * If p == q then rank(p) == rank(q)
 * If p > q then rank(p) > rank(q)
 * The rank should be as small as possible.
 * It is guaranteed that answer is unique under the given rules.
 *
 *
 * Example 1:
 * Input: matrix = [[1,2],[3,4]]
 * Output: [[1,2],[2,3]]
 * Explanation:
 * The rank of matrix[0][0] is 1 because it is the smallest integer in its row
 * and column. The rank of matrix[0][1] is 2 because matrix[0][1] > matrix[0][0]
 * and matrix[0][0] is rank 1. The rank of matrix[1][0] is 2 because
 * matrix[1][0] > matrix[0][0] and matrix[0][0] is rank 1. The rank of
 * matrix[1][1] is 3 because matrix[1][1] > matrix[0][1], matrix[1][1] >
 * matrix[1][0], and both matrix[0][1] and matrix[1][0] are rank 2.
 *
 * Example 2:
 * Input: matrix = [[7,7],[7,7]]
 * Output: [[1,1],[1,1]]
 *
 * Example 3:
 * Input: matrix = [
 *  [20,-21,14],
 *  [-19,4,19],
 *  [22,-47,24],
 *  [-19,4,19]]
 * Output: [[4,2,3],[1,3,4],[5,1,6],[1,3,4]]
 *
 * Example 4:
 * Input: matrix = [[7,3,6],[1,4,5],[9,8,2]]
 * Output: [[5,1,4],[1,2,3],[6,3,1]]
 *
 * Constraints:
 *
 * m == matrix.length
 * n == matrix[i].length
 * 1 <= m, n <= 500
 * -10*9 <= matrix[row][col] <= 10*9
 */
class Solution
{
public:
    std::vector<std::vector<int>> matrixRankTransform(std::vector<std::vector<int>> const& matrix)
    {
        const int rows = static_cast<int>(std::size(matrix));
        const int cols = static_cast<int>(std::size(matrix.front()));
        struct Cell
        {
            int row   = 0;
            int col   = 0;
            int value = 0;
        };
        std::vector<Cell> cells;
        cells.reserve(cols * rows);
        int rowNum = 0;
        for (auto const& row : matrix)
        {
            int colNum = 0;
            for (auto const& value : row)
            {
                cells.push_back({rowNum, colNum, value});
                ++colNum;
            }
            ++rowNum;
        }
        std::sort(  //
            std::begin(cells),
            std::end(cells),
            [](auto const& left, auto const& right)
            {
                return left.value < right.value;
            });

        std::vector<int> maxColRank(cols);
        std::vector<int> maxRowRank(rows);
        std::vector<std::vector<int>> result(rows, std::vector(cols, 0));

        for (auto it = std::begin(cells); it != std::end(cells);)
        {
            auto it1 = it;
            std::unordered_map<int, std::vector<decltype(it)>> rowIndex;
            std::unordered_map<int, std::vector<decltype(it)>> colIndex;
            for (; it1 != std::end(cells) && it1->value == it->value; ++it1)
            {
                rowIndex[it1->row].push_back(it1);
                colIndex[it1->col].push_back(it1);
            }
            std::vector<bool> related(it1 - it);
            std::stack<decltype(it)> toCheck;
            toCheck.push(it);
            while (!toCheck.empty())
            {
                related[toCheck.top() - it] = 1;
                auto [row, col, _]          = *toCheck.top();
                toCheck.pop();
                if (rowIndex.count(row))
                {
                    for (auto next : rowIndex[row])
                        toCheck.push(next);
                    rowIndex.erase(row);
                }
                if (colIndex.count(col))
                {
                    for (auto next : colIndex[col])
                        toCheck.push(next);
                    colIndex.erase(col);
                }
            }

            auto fromIt = it;
            auto toIt   = it;
            auto rank   = 0;
            for (bool isRelated : related)
            {
                if (isRelated)
                {
                    rank = std::max(rank,
                                    std::max(maxColRank[fromIt->col],
                                             maxRowRank[fromIt->row]));
                    std::swap(*toIt, *fromIt);
                    ++toIt;
                }
                ++fromIt;
            }
            ++rank;
            for (; it != toIt; ++it)
            {
                result[it->row][it->col] = rank;
                maxRowRank[it->row]      = rank;
                maxColRank[it->col]      = rank;
            }
        }
        return result;
    }
};

namespace
{
TEST(SolutionTests, All)
{
    using namespace ::testing;

    auto solution4 = Solution{}.matrixRankTransform(
        std::vector{std::vector{7, 7}, std::vector{7, 7}});
    EXPECT_THAT(solution4,
                ElementsAre(  //
                    ElementsAre(1, 1),
                    ElementsAre(1, 1)));

    auto solution1 = Solution{}.matrixRankTransform(  //
        std::vector{std::vector{-37, -50, -3, 44},
                    std::vector{-37, 46, 13, -32},
                    std::vector{47, -42, -3, -40},
                    std::vector{-17, -22, -39, 24}});
    EXPECT_THAT(solution1,
                ElementsAre(  //
                    ElementsAre(2, 1, 4, 6),
                    ElementsAre(2, 6, 5, 4),
                    ElementsAre(5, 2, 4, 3),
                    ElementsAre(4, 3, 1, 5)));

    auto solution6 = Solution{}.matrixRankTransform(  //
        std::vector{                                  //
                    std::vector{-37, -26, -47, -40, -13},
                    std::vector{22, -11, -44, 47, -6},
                    std::vector{-35, 8, -45, 34, -31},
                    std::vector{-16, 23, -6, -43, -20},
                    std::vector{47, 38, -27, -8, 43}});
    EXPECT_THAT(solution6,    //
                ElementsAre(  //
                    ElementsAre(3, 4, 1, 2, 7),
                    ElementsAre(9, 5, 3, 10, 8),
                    ElementsAre(4, 6, 2, 7, 5),
                    ElementsAre(7, 9, 8, 1, 6),
                    ElementsAre(12, 10, 4, 5, 11)));

    auto solution2 = Solution{}.matrixRankTransform(  //
        std::vector{                                  //
                    std::vector{20, -21, 14},
                    std::vector{-19, 4, 19},
                    std::vector{22, -47, 24},
                    std::vector{-19, 4, 19}});
    EXPECT_THAT(solution2,
                ElementsAre(  //
                    ElementsAre(4, 2, 3),
                    ElementsAre(1, 3, 4),
                    ElementsAre(5, 1, 6),
                    ElementsAre(1, 3, 4)));

    auto solution3 = Solution{}.matrixRankTransform(
        std::vector{std::vector{1, 2}, std::vector{3, 4}});
    EXPECT_THAT(solution3,
                ElementsAre(  //
                    ElementsAre(1, 2),
                    ElementsAre(2, 3)));

    auto solution5 = Solution{}.matrixRankTransform(  //
        std::vector{                                  //
                    std::vector{7, 3, 6},
                    std::vector{1, 4, 5},
                    std::vector{9, 8, 2}});
    EXPECT_THAT(solution5,
                ElementsAre(  //
                    ElementsAre(5, 1, 4),
                    ElementsAre(1, 2, 3),
                    ElementsAre(6, 3, 1)));
}
}  // unnamed namespace