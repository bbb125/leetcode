#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/613/week-1-august-1st-august-7th/3870/
 * problem:
 * Alex and Lee play a game with piles of stones.  There are an even number of
 * piles arranged in a row, and each pile has a positive integer number of
 * stones piles[i].
 *
 * The objective of the game is to end with the most stones.  The total number
 * of stones is odd, so there are no ties.
 *
 * Alex and Lee take turns, with Alex starting first.  Each turn, a player takes
 * the entire pile of stones from either the beginning or the end of the row.
 * This continues until there are no more piles left, at which point the person
 * with the most stones wins.
 *
 * Assuming Alex and Lee play optimally, return True if and only if Alex wins
 * the game.
 *
 *
 *
 * Example 1:
 * Input: piles = [5,3,4,5]
 * Output: true
 * Explanation:
 * Alex starts first, and can only take the first 5 or the last 5.
 * Say he takes the first 5, so that the row becomes [3, 4, 5].
 * If Lee takes 3, then the board is [4, 5], and Alex takes 5 to win with 10
 * points. If Lee takes the last 5, then the board is [3, 4], and Alex takes 4
 * to win with 9 points. This demonstrated that taking the first 5 was a winning
 * move for Alex, so we return true.
 *
 *
 * Constraints:
 * 2 <= piles.length <= 500
 * piles.length is even.
 * 1 <= piles[i] <= 500
 * sum(piles) is odd.
 */

class Solution
{
public:
    bool stoneGame(std::vector<int> const& piles)
    {
        struct GameResult
        {
            int playerA_ = 0;
            int playerB_ = 0;
        };
        const int pilesSize = static_cast<int>(std::size(piles));
        std::vector<GameResult> gameResults(pilesSize);
        for (int i = 0; i < pilesSize - 1; ++i)
            gameResults[i] = GameResult{
                .playerA_ = std::max(piles[i], piles[i + 1]),
                .playerB_ = std::min(piles[i], piles[i + 1]),
            };

        for (int size = 2; size < pilesSize; ++size)
        {
            for (int j = 0; j < (pilesSize - size); ++j)
            {
                const int maxIndex  = gameResults[j].playerB_ + piles[j + size]
                                           > gameResults[j + 1].playerB_ + piles[j]
                                        ? j
                                        : j + 1;
                const int pileIndex = j == maxIndex ? j + size : j;
                gameResults[j]      = GameResult{
                    .playerA_ = gameResults[maxIndex].playerB_ + piles[pileIndex],
                    .playerB_ = gameResults[maxIndex].playerA_};
            }
        }
        return gameResults[0].playerA_ > gameResults[0].playerB_;
    }
};

// The solution above mimics the dynamic programming technique. However,
// it's possible to prove mathematically that the result is always `true`.
// If we consider 4 piles case:
// p1, p2, p3, p4
// they can't be all equal. Because we guaranteed that number of stones is odd
// and there can not be a tie.
// So let's look at all winning combinations
// p1, p2
// p1, p4
// p2, p3
// p3, p4
// those combinations can't be winning, because player one can take the only one
// of those piles, second one will be available to the player two.
//
// p1, p3
// p2, p4
// so we can choose which one of this is winning and follow this strategy.
//
namespace smart_solution
{
class Solution
{
public:
    bool stoneGame(std::vector<int> const&)
    {
        return true;
    }
};
}  // namespace smart_solution
namespace
{
    TEST(SolutionTests, All)
    {
        EXPECT_TRUE(Solution{}.stoneGame({10, 7, 2, 6}));
        EXPECT_TRUE(Solution{}.stoneGame({3, 7, 2, 3}));
        EXPECT_TRUE(Solution{}.stoneGame({5, 3, 4, 5}));
    }
}  // unnamed namespace