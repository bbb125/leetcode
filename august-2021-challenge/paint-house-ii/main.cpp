#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/615/week-3-august-15th-august-21st/3890/
 * problem:
 * There are a row of n houses, each house can be painted with one of the k colors.
 The cost of painting each house with a certain color is different. You have to
 paint all the houses such that no two adjacent houses have the same color.
 *
 * The cost of painting each house with a certain color is represented by an n x k cost matrix costs.
 *
 * For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2]
 is the cost of painting house 1 with color 2, and so on...
 * Return the minimum cost to paint all houses.
 *
 *
 * Example 1:
 * Input: costs = [[1,5,3],[2,9,4]]
 * Output: 5
 * Explanation:
 * Paint house 0 into color 0, paint house 1 into color 2. Minimum cost: 1 + 4 = 5;
 * Or paint house 0 into color 2, paint house 1 into color 0. Minimum cost: 3 + 2 = 5.
 *
 * Example 2:
 * Input: costs = [[1,3],[2,4]]
 * Output: 5
 *
 *
 * Constraints:
 *
 * costs.length == n
 * costs[i].length == k
 * 1 <= n <= 100
 * 1 <= k <= 20
 * 1 <= costs[i][j] <= 20
 *
 * Follow up: Could you solve it in O(nk) runtime?
 */
 /**
  * Here is an evolution of dynamic programming approach, to something more efficient.
  * Reducing O(N*K*K) to O(N*K) was a good improvement, the rest was done just for fun.
  */
class Solution
{
public:
    int minCostII(std::vector<std::vector<int>> const& costs)
    {
        const int housesSize = static_cast<int>(std::size(costs));
        const int colorsSize = static_cast<int>(std::size(costs.front()));
        //std::vector<int> result(colorsSize, 0);
        std::pair<int, int> best{-1, -1};
        std::pair<int, int> bestResult{0, 0};
        for (int i = 0; i < housesSize; ++i)
        {
            std::pair<int, int> newBest{-1, -1};
            std::pair<int, int> newBestResult{0, 0};
            for (int j = 0; j < colorsSize; ++j)
            {
                int result = 0;
                if (j == best.first)
                    result = bestResult.second + costs[i][j];
                else
                {
                    result = ((best.first != -1) ? bestResult.first : 0)
                               + costs[i][j];
                }
                if (newBest.first == -1 || result < newBestResult.first)
                {
                    newBest.second = newBest.first;
                    newBestResult.second = newBestResult.first;
                    newBest.first = j;
                    newBestResult.first = result;
                }
                if ((newBest.second == -1
                    || (result <= newBestResult.second)) && j != newBest.first)
                {
                    newBest.second = j;
                    newBestResult.second = result;
                }
            }
            std::swap(newBestResult, bestResult);
            std::swap(newBest, best);
        }

        if (best.first == -1)
            return bestResult.second;
        else if (best.second == -1)
            return bestResult.first;

        return std::min(bestResult.first, bestResult.second);
    }
};
namespace
{
TEST(SolutionTests, All)
{
    //    Input:
    //    [[8,16,12,18,9],[19,18,8,2,8],[8,5,5,13,4],[15,9,3,19,2],[8,7,1,8,17],[8,2,8,15,5],[8,17,1,15,3],[8,8,5,5,16],[2,2,18,2,9]]
    //    Output:
    //    35
    //    Expected:
    //    28
    EXPECT_EQ(8, Solution{}.minCostII({std::vector{8}}));
    EXPECT_EQ(28,
        Solution{}.minCostII({//
            std::vector{8, 16, 12, 18, 9},
            std::vector{19, 18, 8, 2, 8},
            std::vector{8, 5, 5, 13, 4},
            std::vector{15, 9, 3, 19, 2},
            std::vector{8, 7, 1, 8, 17},
            std::vector{8, 2, 8, 15, 5},
            std::vector{8, 17, 1, 15, 3},
            std::vector{8, 8, 5, 5, 16},
            std::vector{2, 2, 18, 2, 9}}));
    EXPECT_EQ(5, Solution{}.minCostII({std::vector{1, 5, 3}, std::vector{2, 9, 4}}));
    EXPECT_EQ(5, Solution{}.minCostII({std::vector{1, 3}, std::vector{2, 4}}));

}
}  // unnamed namespace