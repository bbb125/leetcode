#include <gtest/gtest.h>

#include <vector>
#include <stack>
#include <unordered_set>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/613/week-1-august-1st-august-7th/3835/
 *
 * problem:
 * You are given an n x n binary matrix grid. You are allowed to change at most
 * one 0 to be 1.
 * Return the size of the largest island in grid after applying this operation.
 * An island is a 4-directionally connected group of 1s.
 *
 * Example 1:
 * Input: grid = [[1,0],[0,1]]
 * Output: 3
 * Explanation: Change one 0 to 1 and connect two 1s, then we get an island with
 * area = 3.
 *
 * Example 2:
 * Input: grid = [[1,1],[1,0]]
 * Output: 4
 * Explanation: Change the 0 to 1 and make the island bigger, only one island
 * with area = 4.
 *
 * Example 3:
 * Input: grid = [[1,1],[1,1]]
 * Output: 4
 * Explanation: Can't change any 0 to 1, only one island with area = 4.
 *
 *
 * Constraints:
 * n == grid.length
 * n == grid[i].length
 * 1 <= n <= 500
 * grid[i][j] is either 0 or 1.
 */
namespace
{
struct Hash
{
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};
using Grid       = std::vector<std::vector<int>>;
using Coordinate = std::pair<int, int>;
using Direction  = Coordinate;

Coordinate moveBy(Coordinate const& position, Direction const& direction)
{
    return {position.first + direction.first, position.second + direction.second};
}

bool validPosition(int gridSize, Coordinate const& position)
{
    auto [x, y] = position;
    return x >= 0 && x < gridSize && y >= 0 && y < gridSize;
}

std::array<Direction, 4> movements{// no-format
                                   Direction{-1, 0},
                                   Direction{1, 0},
                                   Direction{0, -1},
                                   Direction{0, 1}};
template<typename Func>
void forAllMovements(int gridSize, Coordinate position, Func func)
{
    for (auto const& movement : movements)
    {
        auto newPosition = moveBy(position, movement);
        if (validPosition(gridSize, newPosition))
            func(newPosition);
    }
}

int getGridValue(Grid const& grid, Coordinate const& position)
{
    return grid[position.first][position.second];
}

void setGridValue(Grid& grid, Coordinate const& position, int value)
{
    grid[position.first][position.second] = value;
}

}  // unnamed namespace
class Solution
{
public:
    int fill(Grid& grid, Coordinate start, int color)
    {
        const int gridSize = static_cast<int>(std::size(grid));
        std::unordered_set<Coordinate, Hash> toVisit{start};
        std::unordered_set<Coordinate, Hash> visited;
        int islandSize = 0;
        while (!toVisit.empty())
        {
            auto position = *std::begin(toVisit);
            toVisit.erase(position);
            if (getGridValue(grid, position) == color)
                continue;
            setGridValue(grid, position, color);
            islandSize += 1;
            forAllMovements(  // no-format
                gridSize,
                position,
                [&](auto& newPosition)
                {
                    if (visited.count(newPosition) != 0
                        || getGridValue(grid, newPosition) != 1)
                        return;
                    toVisit.insert(newPosition);
                });
            visited.insert(position);
        }
        return islandSize;
    }

    int largestIsland(Grid& grid)
    {
        // compute sizes of all islands O(N**2)
        // brute-force solution in O(N**2)
        const int size = static_cast<int>(std::size(grid));
        std::vector<int> islandsSizes(2, 0);  // indexing starts with two

        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (grid[i][j] != 1)  // already marked or water
                    continue;
                islandsSizes.push_back(
                    fill(grid, {i, j}, static_cast<int>(std::size(islandsSizes))));
            }
        }

        int result = 0;
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                Coordinate position{i, j};
                int sum = 1;
                if (getGridValue(grid, position) == 0)
                {
                    std::array<int, 4> neighborIslands = {};
                    int num                            = 0;
                    forAllMovements(  // no-format
                        size,
                        position,
                        [&](auto& newPosition)
                        {
                            neighborIslands[num++] = getGridValue(grid, newPosition);
                        });
                    std::sort(std::begin(neighborIslands), std::end(neighborIslands));
                    for (int k = 0; k < 4; ++k)
                        if (k == 0 || neighborIslands[k] != neighborIslands[k - 1])
                            sum += islandsSizes[neighborIslands[k]];
                }
                else
                    sum = islandsSizes[getGridValue(grid, position)];
                if (result <= sum)
                    result = sum;
            }
        }

        return result;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    /**
     * Example 1:
     * Input: grid = [[1,0],[0,1]]
     * Output: 3
     * Explanation: Change one 0 to 1 and connect two 1s, then we get an island
     * with area = 3.
     */
    Grid example1 = {{1, 0}, {0, 1}};
    EXPECT_EQ(3, Solution{}.largestIsland(example1));
    /**
     * Example 2:
     * Input: grid = [[1,1],[1,0]]
     * Output: 4
     * Explanation: Change the 0 to 1 and make the island bigger, only one
     * island with area = 4.
     */
    Grid example2 = {{1, 1}, {1, 0}};
    EXPECT_EQ(4, Solution{}.largestIsland(example2));
    /**
     * Example 3:
     * Input: grid = [[1,1],[1,1]]
     * Output: 4
     * Explanation: Can't change any 0 to 1, only one island with area = 4.
     */
    Grid example3 = {{1, 1}, {1, 1}};
    EXPECT_EQ(4, Solution{}.largestIsland(example3));
}
}  // unnamed namespace