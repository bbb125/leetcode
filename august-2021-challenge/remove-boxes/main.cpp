#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3889/
 * problem:
 * You are given several boxes with different colors represented by different
 * positive numbers.
 *
 * You may experience several rounds to remove boxes until there is no box left.
 * Each time you can choose some continuous boxes with the same color (i.e.,
 * composed of k boxes, k >= 1), remove them and get k * k points.
 *
 * Return the maximum points you can get.
 *
 * Example 1:
 * Input: boxes = [1,3,2,2,2,3,4,3,1]
 * Output: 23
 * Explanation:
 * [1, 3, 2, 2, 2, 3, 4, 3, 1]
 * ----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
 * ----> [1, 3, 3, 3, 1] (1*1=1 points)
 * ----> [1, 1] (3*3=9 points)
 * ----> [] (2*2=4 points)
 *
 *
 * Example 2:
 * Input: boxes = [1,1,1]
 * Output: 9
 *
 * Example 3:
 * Input: boxes = [1]
 * Output: 1
 *
 * Constraints:
 * 1 <= boxes.length <= 100
 * 1 <= boxes[i] <= 100
 */
class Solution
{
public:
    /**
     * Idea was taken from the published solution for educational purposes.
     */
    struct Impl
    {
        Impl(std::vector<int> const& boxes)
            : boxes_{boxes}
        {}

        int solve() const
        {
            return solve(0, static_cast<int>(std::size(boxes_)) - 1, 0);
        }

        int solve(int left, int right, int remove) const
        {
            if (left > right)
                return 0;

            while (left < right && boxes_[right] == boxes_[right - 1])
            {
                --right;
                ++remove;
            }

            if (cache_[left][right][remove] != 0)
                return cache_[left][right][remove];

            int result = solve(left, right - 1, 0) + (remove + 1) * (remove + 1); // remove all contiguous elements

            /*
             * In our case recursive solution would look like:
             * for every box `I` between Left, Right
             *     if box[I] has the same color as right
             *        we try to remove boxes in the middle(solution(I + 1, Right - 1))
             *        and we solve part [Left, I] assuming that +1 elements can
             *        be removed in one shot (solution(Left, I, remove + 1))
             * an extra case - remove all contiguous elements ((remove + 1) ^ 2)
             * and solve for Left, Right - 1.
             *
             * This representation is great, because recursion may be represented
             * via three integers (Left, Right, Elements we can already remove
             * from the Right side).
             * That means that we can easily do memoization.
             *
             */
            for (int i = left; i < right; ++i)
                if (boxes_[i] == boxes_[right])
                    result = std::max(result,
                        solve(left, i, remove + 1) //
                            + solve(i + 1, right - 1, 0));
            return (cache_[left][right][remove] = result);
        }

        static constexpr int maxElements = 100;
        mutable std::array<std::array<std::array<int, maxElements>, maxElements>, maxElements> cache_{};

        std::vector<int> const& boxes_;
    };

    int removeBoxes(std::vector<int> const& boxes)
    {
        return Impl{boxes}.solve();
    }
};

namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(23, Solution{}.removeBoxes({1, 3, 2, 2, 2, 3, 4, 3, 1}));
    EXPECT_EQ(9, Solution{}.removeBoxes({1, 1, 1}));
    EXPECT_EQ(1, Solution{}.removeBoxes({1}));
}
} // unnamed namespace