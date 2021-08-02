#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <vector>

/**
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it can trap after raining.
 *
 * Example 1:
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The above elevation map (black section) is represented by
 * array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue
 * section) are being trapped.
 *
 * Example 2:
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 *
 *
 * Constraints:
 *      n == height.length
 *      0 <= n <= 3 * 104
 *      0 <= height[i] <= 105
 */

class Solution
{
public:
    int trap(std::vector<int> const& heights)
    {
        using Bar = std::pair<int, int>;
        std::vector<Bar> bars;

        const int size = static_cast<int>(std::size(heights));
        int sum        = 0;
        for (int i = 0; i < size; ++i)
        {
            if (bars.empty())
            {
                bars.emplace_back(heights[i], i);
                continue;
            }
            auto activeHeight = std::min(bars.front().first, heights[i]);
            int lastProcessedPosition = i;
            while (!bars.empty() && bars.back().first <= heights[i])
            {
                auto [height, currentPosition] = bars.back();
                sum += (lastProcessedPosition - currentPosition) * (activeHeight - height);
                bars.pop_back();
                lastProcessedPosition = currentPosition;
            }
            bars.emplace_back(heights[i], lastProcessedPosition);
        }
        return sum;
    }
};

/**
 * note: dynamic programming is really nice
 * for every position compute  max to the left and max to the right
 * then for every positions sum += min(max-to-the-left, max-to-the-right) - height
 */

namespace
{
TEST(SolutionTests, All)
{
    //    * Example 1:
    //    * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
    //        * Output: 6
    //        * Explanation: The above elevation map (black section) is represented by
    //        * array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue
    //        * section) are being trapped.
    //        *
    //        * Example 2:
    //        * Input: height = [4,2,0,3,2,5]
    //            * Output: 9
    EXPECT_EQ(Solution{}.trap({4,2,0,3,2,5}), 9);
    EXPECT_EQ(Solution{}.trap({2,1,0,1,3}), 4);
    EXPECT_EQ(Solution{}.trap({0,1,0,2,1,0,1,3,2,1,2,1}), 6);


}
}  // namespace
