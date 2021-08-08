#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
/**
 * url: https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/
 * problem:
 * You want to build some obstacle courses. You are given a 0-indexed integer
 * array obstacles of length n, where obstacles[i] describes the height of the
 * ith obstacle.
 *
 * For every index i between 0 and n - 1 (inclusive), find the length of the
 * longest obstacle course in obstacles such that:
 *
 * You choose any number of obstacles between 0 and i inclusive.
 * You must include the ith obstacle in the course.
 * You must put the chosen obstacles in the same order as they appear in
 * obstacles. Every obstacle (except the first) is taller than or the same
 * height as the obstacle immediately before it. Return an array ans of length
 * n, where ans[i] is the length of the longest obstacle course for index i as
 * described above.
 *
 *
 * Example 1:
 * Input: obstacles = [1,2,3,2]
 * Output: [1,2,3,3]
 * Explanation: The longest valid obstacle course at each position is:
 * - i = 0: [1], [1] has length 1.
 * - i = 1: [1,2], [1,2] has length 2.
 * - i = 2: [1,2,3], [1,2,3] has length 3.
 * - i = 3: [1,2,3,2], [1,2,2] has length 3.
 *
 * Example 2:
 * Input: obstacles = [2,2,1]
 * Output: [1,2,1]
 * Explanation: The longest valid obstacle course at each position is:
 * - i = 0: [2], [2] has length 1.
 * - i = 1: [2,2], [2,2] has length 2.
 * - i = 2: [2,2,1], [1] has length 1.
 *
 * Example 3:
 * Input: obstacles = [3,1,5,6,4,2]
 * Output: [1,1,2,3,2,2]
 * Explanation: The longest valid obstacle course at each position is:
 * - i = 0: [3], [3] has length 1.
 * - i = 1: [3,1], [1] has length 1.
 * - i = 2: [3,1,5], [3,5] has length 2. [1,5] is also valid.
 * - i = 3: [3,1,5,6], [3,5,6] has length 3. [1,5,6] is also valid.
 * - i = 4: [3,1,5,6,4], [3,4] has length 2. [1,4] is also valid.
 * - i = 5: [3,1,5,6,4,2], [1,2] has length 2.
 *
 *
 * Constraints:
 *
 * n == obstacles.length
 * 1 <= n <= 105
 * 1 <= obstacles[i] <= 107
 */
namespace slow
{
class Solution
{
public:
    std::vector<int> longestObstacleCourseAtEachPosition(std::vector<int> const& obstacles)
    {
        const int size = static_cast<int>(std::size(obstacles));
        std::vector<int> result(size, 1);
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (obstacles[j] <= obstacles[i] && result[i] <= result[j])
                    result[i] = result[j] + 1;
            }
        }
        return result;
    }
};
}  // namespace slow
namespace fast
{
class Solution
{
public:
    std::vector<int> longestObstacleCourseAtEachPosition(std::vector<int> const& obstacles)
    {
        const int size = static_cast<int>(std::size(obstacles));
        int max = *std::max_element(std::begin(obstacles), std::end(obstacles));
        std::vector<int> cache(max, 0);
        std::vector<int> result(size, 1);

        for (int i = 0; i < size; ++i)
        {
            auto it             = std::max_element(std::begin(cache),
                                                   std::begin(cache) + obstacles[i] + 1);
            result[i]           = *it + 1;
            cache[obstacles[i]] = result[i];
        }
        return result;
    }
};
}  // namespace fast
namespace really_fast
{
class Solution
{
public:
    // the idea is taken from the discussion and wikipedia
    // https://en.wikipedia.org/wiki/Longest_increasing_subsequence
    std::vector<int> longestObstacleCourseAtEachPosition(std::vector<int> const& nums)
    {
        std::vector<int> result;
        std::vector<int> runningResult;
        for (int i = 0; i < static_cast<int>(std::size(nums)); ++i)
        {
            int x = nums[i];
            if (runningResult.empty() || runningResult.back() <= x)
            {
                runningResult.push_back(x);
                result.push_back(runningResult.size());
            }
            else
            {
                int idx = std::upper_bound(runningResult.begin(), runningResult.end(), x)
                        - runningResult.begin();
                runningResult[idx] = x;
                result.push_back(idx + 1);
            }
        }
        return result;
    }
};
}  // namespace really_fast
namespace
{
TEST(SolutionTests, All)
{
    using namespace really_fast;
    Solution{}.longestObstacleCourseAtEachPosition({2, 2, 5, 2, 2, 5, 2, 2});
    EXPECT_THAT(Solution{}.longestObstacleCourseAtEachPosition({2, 2, 1}),
                ::testing::ElementsAre(1, 2, 1));
    EXPECT_THAT(Solution{}.longestObstacleCourseAtEachPosition({3, 1, 5, 6, 4, 2}),
                ::testing::ElementsAre(1, 1, 2, 3, 2, 2));
    EXPECT_THAT(Solution{}.longestObstacleCourseAtEachPosition({1, 2, 3, 2}),
                ::testing::ElementsAre(1, 2, 3, 3));
}
}  // unnamed namespace