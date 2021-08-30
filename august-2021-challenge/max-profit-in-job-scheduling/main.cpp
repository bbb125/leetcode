#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <numeric>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/616/week-4-august-22nd-august-28th/3950/
 * problem:
 * We have n jobs, where every job is scheduled to be done from startTime[i] to
 * endTime[i], obtaining a profit of profit[i].
 *
 * You're given the startTime, endTime and profit arrays, return the maximum
 * profit you can take such that there are no two jobs in the subset with
 * overlapping time range.
 *
 * If you choose a job that ends at time X you will be able to start another job
 * that starts at time X.
 *
 * Example 1:
 * Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
 * Output: 120
 * Explanation: The subset chosen is the first and fourth job.
 * Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
 *
 * Example 2:
 * Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit =
 * [20,20,100,70,60] Output: 150 Explanation: The subset chosen is the first,
 * fourth and fifth job. Profit obtained 150 = 20 + 70 + 60.
 *
 * Example 3:
 * Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
 * Output: 6
 *
 * Constraints:
 *
 * 1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
 * 1 <= startTime[i] < endTime[i] <= 10^9
 * 1 <= profit[i] <= 10^4
 */
class Solution
{
public:
    int jobScheduling(std::vector<int> const& startTime,
        std::vector<int> const& endTime,
        std::vector<int> const& profit)
    {
        const std::size_t schedulesSize = std::size(startTime);

        struct Job
        {
            int startsAt_ = 0;
            int endsAt_   = 0;
            int profit_   = 0;
        };
        std::vector<Job> jobs;
        jobs.reserve(schedulesSize);
        for (std::size_t i = 0; i < schedulesSize; ++i)
            jobs.push_back({startTime[i], endTime[i], profit[i]});
        std::sort(std::begin(jobs),
            std::end(jobs),
            [](auto const& left, auto const& right)
            {
                return left.startsAt_ < right.startsAt_;
            });

        std::map<int, int, std::greater<>> profitEndTimeLookup;
        for (auto const job : jobs)
        {
            auto currentProfit = [&profitEndTimeLookup, &job]
            {
                auto it = std::find_if(std::begin(profitEndTimeLookup),
                    std::end(profitEndTimeLookup),
                    [startsAt = job.startsAt_](auto const& value)
                    {
                        return value.second <= startsAt;
                    });
                return job.profit_
                     + ((it != std::end(profitEndTimeLookup)) ? it->first : 0);
            }();

            auto& currentProfitEndTime = profitEndTimeLookup[currentProfit];
            if (currentProfitEndTime == 0 || currentProfitEndTime >= job.endsAt_)
                currentProfitEndTime = job.endsAt_;
        }
        return std::begin(profitEndTimeLookup)->first;
    }
};

namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(41,
        Solution{}.jobScheduling({6, 15, 7, 11, 1, 3, 16, 2},
            {19, 18, 19, 16, 10, 8, 19, 8},
            {2, 9, 1, 19, 5, 7, 3, 19}));
    EXPECT_EQ(120, Solution{}.jobScheduling({1, 2, 3, 4}, {3, 4, 5, 6}, {50, 10, 40, 70}));
    EXPECT_EQ(150,
        Solution{}.jobScheduling({1, 2, 3, 4, 6}, {3, 5, 10, 6, 9}, {20, 20, 100, 70, 60}));
    EXPECT_EQ(6, Solution{}.jobScheduling({1, 1, 1}, {2, 3, 4}, {5, 6, 4}));
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace