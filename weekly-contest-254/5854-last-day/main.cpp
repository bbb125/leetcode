#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * problem:
 */

class Solution
{
public:
    int latestDayToCross(int row, int col, std::vector<std::vector<int>> const& cells)
    {
        std::vector<std::vector<int>> map(row, std::vector<int>(col, 0));
        decltype(map) workingMap(row, std::vector<int>(col, 0));
        for (std::size_t i = 0; i < std::size(cells); ++i)
            map[cells[i][0] - 1][cells[i][1] - 1] = i;
        workingMap[0] = map[0];

        for (int i = 1; i < row; ++i)
        {

            for (int j = 0; j < col; ++j)
            {
                if (i > 0)
                    workingMap[i][j] = std::min(map[i - 1][j], map[i][j]);
                workingMap[i][j] = std::min(workingMap[i - 1][j], map[i][j]);
            }
            bool changed = true;
            while (changed)
            {
                changed = false;
                for (int j = 0; j < col; ++j)
                {
                    auto previous = workingMap[i][j];
                    if (j < (col - 1)
                        && workingMap[i][j] < std::min(map[i][j], workingMap[i][j + 1]))
                        workingMap[i][j] = std::min(map[i][j], workingMap[i][j + 1]);
                    if (j > 0 && workingMap[i][j] < std::min(map[i][j], workingMap[i][j - 1]))
                        workingMap[i][j] = std::min(map[i][j], workingMap[i][j - 1]);
                    changed |= (workingMap[i][j] != previous);
                }
            }
        }
        auto const& last = workingMap.back();
        return *std::max_element(std::begin(last), std::end(last));
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(35,
     Solution{}.latestDayToCross(13,
      9,
      std::vector{{12, 6},
       std::vector{3, 4},
       std::vector{2, 9},
       std::vector{9, 4},
       std::vector{9, 2},
       std::vector{6, 4},
       std::vector{4, 4},
       std::vector{8, 6},
       std::vector{4, 9},
       std::vector{5, 6},
       std::vector{7, 5},
       std::vector{12, 4},
       std::vector{11, 8},
       std::vector{3, 7},
       std::vector{2, 6},
       std::vector{9, 8},
       std::vector{3, 5},
       std::vector{13, 4},
       std::vector{1, 3},
       std::vector{10, 2},
       std::vector{8, 9},
       std::vector{6, 6},
       std::vector{11, 7},
       std::vector{11, 1},
       std::vector{13, 9},
       std::vector{12, 7},
       std::vector{10, 7},
       std::vector{8, 2},
       std::vector{1, 8},
       std::vector{7, 3},
       std::vector{6, 5},
       std::vector{2, 1},
       std::vector{10, 6},
       std::vector{4, 8},
       std::vector{4, 2},
       std::vector{9, 7},
       std::vector{6, 2},
       std::vector{3, 6},
       std::vector{12, 2},
       std::vector{10, 3},
       std::vector{10, 5},
       std::vector{9, 5},
       std::vector{8, 8},
       std::vector{8, 7},
       std::vector{3, 2},
       std::vector{13, 6},
       std::vector{3, 1},
       std::vector{5, 1},
       std::vector{2, 7},
       std::vector{8, 3},
       std::vector{12, 5},
       std::vector{11, 2},
       std::vector{6, 3},
       std::vector{1, 4},
       std::vector{13, 3},
       std::vector{4, 1},
       std::vector{9, 9},
       std::vector{7, 7},
       std::vector{4, 3},
       std::vector{12, 1},
       std::vector{2, 2},
       std::vector{7, 6},
       std::vector{4, 6},
       std::vector{7, 9},
       std::vector{7, 2},
       std::vector{3, 8},
       std::vector{1, 6},
       std::vector{11, 3},
       std::vector{11, 4},
       std::vector{5, 9},
       std::vector{13, 8},
       std::vector{1, 9},
       std::vector{10, 1},
       std::vector{9, 1},
       std::vector{6, 1},
       std::vector{10, 9},
       std::vector{12, 9},
       std::vector{11, 5},
       std::vector{8, 1},
       std::vector{13, 5},
       std::vector{9, 6},
       std::vector{13, 2},
       std::vector{6, 8},
       std::vector{2, 8},
       std::vector{5, 3},
       std::vector{3, 3},
       std::vector{13, 1},
       std::vector{11, 9},
       std::vector{9, 3},
       std::vector{2, 4},
       std::vector{5, 2},
       std::vector{8, 5},
       std::vector{13, 7},
       std::vector{12, 8},
       std::vector{5, 5},
       std::vector{7, 1},
       std::vector{7, 4},
       std::vector{2, 5},
       std::vector{6, 9},
       std::vector{4, 7},
       std::vector{5, 8},
       std::vector{1, 5},
       std::vector{10, 8},
       std::vector{8, 4},
       std::vector{1, 1},
       std::vector{3, 9},
       std::vector{1, 2},
       std::vector{7, 8},
       std::vector{1, 7},
       std::vector{6, 7},
       std::vector{11, 6},
       std::vector{4, 5},
       std::vector{5, 7},
       std::vector{2, 3},
       std::vector{10, 4},
       std::vector{5, 4},
       std::vector{12, 3}}));
    EXPECT_EQ(3,
     Solution{}.latestDayToCross(6,
      2,
      std::vector{std::vector{4, 2},
       std::vector{6, 2},
       std::vector{2, 1},
       std::vector{4, 1},
       std::vector{6, 1},
       std::vector{3, 1},
       std::vector{2, 2},
       std::vector{3, 2},
       std::vector{1, 1},
       std::vector{5, 1},
       std::vector{5, 2},
       std::vector{1, 2}}));

    EXPECT_EQ(3,
     Solution{}.latestDayToCross(3,
      3,
      std::vector{std::vector{1, 2},
       std::vector{2, 1},
       std::vector{3, 3},
       std::vector{2, 2},
       std::vector{1, 1},
       std::vector{1, 3},
       std::vector{2, 3},
       std::vector{3, 2},
       std::vector{3, 1}}));

    //    6
    //    2
    //    [[4,2],[6,2],[2,1],[4,1],[6,1],[3,1],[2,2],[3,2],[1,1],[5,1],[5,2],[1,2]]

    std::cout << Solution{}.latestDayToCross(6,
     2,
     std::vector{std::vector{4, 2},
      std::vector{6, 2},
      std::vector{2, 1},
      std::vector{4, 1},
      std::vector{6, 1},
      std::vector{3, 1},
      std::vector{2, 2},
      std::vector{3, 2},
      std::vector{1, 1},
      std::vector{5, 1},
      std::vector{5, 2},
      std::vector{1, 2}})
              << std::endl;
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
} // unnamed namespace