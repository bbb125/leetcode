#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/616/week-4-august-22nd-august-28th/3907/
 * problem:
 * We are given a list of (axis-aligned) rectangles. Each rectangle[i] = [xi1,
 * yi1, xi2, yi2] , where (xi1, yi1) are the coordinates of the bottom-left corner,
 * and (xi2, yi2) are the coordinates of the top-right corner of the ith rectangle.
 *
 * Find the total area covered by all rectangles in the plane. Since the answer
 * may be too large, return it modulo 10e9 + 7.
 *
 * Example 1:
 * Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
 * Output: 6
 * Explanation: As illustrated in the picture.
 *
 * Example 2:
 * Input: rectangles = [[0,0,1000000000,1000000000]]
 * Output: 49
 * Explanation: The answer is 1018 modulo (109 + 7), which is (109)2 = (-7)2 = 49.
 *
 *
 * Constraints:
 *
 * 1 <= rectangles.length <= 200
 * rectanges[i].length = 4
 * 0 <= rectangles[i][j] <= 10^9
 * The total area covered by all rectangles will never exceed 2^63 - 1 and thus
 * will fit in a 64-bit signed integer.
 */
class Solution
{
public:
    int rectangleArea(std::vector<std::vector<int>>& rectangles)
    {
        auto modulo = [](auto value) -> std::int64_t
        {
            constexpr std::int64_t mod = 1e9 + 7;
            return value % mod;
        };
        std::set<int> yLevels;
        for (auto const& rectangle : rectangles)
        {
            yLevels.insert(rectangle[1]);
            yLevels.insert(rectangle[3]);
        }
        std::sort(std::begin(rectangles),
            std::end(rectangles),
            [](auto const& left, auto const& right)
            {
                return left[0] < right[0];
            });

        auto previousLevel = std::begin(yLevels);
        std::int64_t area  = 0;
        for (auto currentLevel = std::next(previousLevel);
             currentLevel != std::end(yLevels);
             ++currentLevel, ++previousLevel)
        {
            std::int64_t xStart = 0;
            std::int64_t xEnd   = 0;
            std::int64_t height = *currentLevel - *previousLevel;
            for (auto const& rectangle : rectangles)
            {
                if (rectangle[1] > *previousLevel || rectangle[3] < *currentLevel)
                    continue;

                if (rectangle[0] > xEnd)
                {
                    area += modulo((xEnd - xStart) * height);
                    xStart = rectangle[0];
                    xEnd   = rectangle[2];
                }
                else
                    xEnd = std::max(xEnd, std::int64_t{rectangle[2]});
            }
            area += modulo((xEnd - xStart) * height);
        }
        return modulo(area);
    }
};
namespace
{
TEST(SolutionTests, All)
{
    std::vector<std::vector<int>> example1{//
        std::vector{0, 0, 2, 2},
        std::vector{1, 0, 2, 3},
        std::vector{1, 0, 3, 1}};
    EXPECT_EQ(6, Solution{}.rectangleArea(example1));

    std::vector<std::vector<int>> example2{//
        std::vector{0, 0, 1000000000, 1000000000}};
    EXPECT_EQ(49, Solution{}.rectangleArea(example2));
}
}  // unnamed namespace