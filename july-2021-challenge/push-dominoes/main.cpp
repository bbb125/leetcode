#include <gtest/gtest.h>

#include <string>
#include <vector>
/**
 * There are n dominoes in a line, and we place each domino vertically upright.
 * In the beginning, we simultaneously push some of the dominoes either to the
 * left or to the right.
 *
 * After each second, each domino that is falling to the left pushes the
 * adjacent domino on the left. Similarly, the dominoes falling to the right
 * push their adjacent dominoes standing on the right.
 *
 * When a vertical domino has dominoes falling on it from both sides, it stays
 * still due to the balance of the forces.
 *
 * For the purposes of this question, we will consider that a falling domino
 * expends no additional force to a falling or already fallen domino.
 *
 * You are given a string dominoes representing the initial state where:
 *
 * dominoes[i] = 'L', if the ith domino has been pushed to the left,
 * dominoes[i] = 'R', if the ith domino has been pushed to the right, and
 * dominoes[i] = '.', if the ith domino has not been pushed.
 * Return a string representing the final state.
 *
 *
 *
 * Example 1:
 * Input: dominoes = "RR.L"
 * Output: "RR.L"
 * Explanation: The first domino expends no additional force on the second
 * domino.
 *
 * Example 2:
 * Input: dominoes = ".L.R...LR..L.."
 * Output: "LL.RR.LLRRLL.."
 *
 *
 * Constraints:
 *
 * n == dominoes.length
 * 1 <= n <= 105
 * dominoes[i] is either 'L', 'R', or '.'.
 */

class Solution
{
public:
    std::string pushDominoes(std::string dominoes)
    {
        dominoes    = 'L' + dominoes + 'R';
        const int n = std::ssize(dominoes);
        std::vector<int> forcePlaces;
        forcePlaces.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            if (dominoes[i] == 'L' || dominoes[i] == 'R')
                forcePlaces.push_back(i);
        }

        std::string result;
        result.reserve(n);

        for (std::size_t i = 0; i < forcePlaces.size() - 1; ++i)
        {
            int batchSize            = forcePlaces[i + 1] - forcePlaces[i] - 1;
            const char currentDomino = dominoes[forcePlaces[i]];
            const char nextDomino    = dominoes[forcePlaces[i + 1]];

            if (i != 0)  // ignore first to compensate artificial element (and don't add last)
                result.push_back(currentDomino);

            if (currentDomino == 'R' && nextDomino == 'L')
            {
                result.append(batchSize / 2, 'R');
                result.append(batchSize % 2, '.');
                result.append(batchSize / 2, 'L');
            }
            else if (currentDomino == 'L' && nextDomino == 'R')
                result.append(batchSize, '.');
            else  // if (currentDomino == nextDomino)
                result.append(batchSize, currentDomino);
        }

        return result;
    }
};

namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(Solution{}.pushDominoes("RR.L"), "RR.L");
    EXPECT_EQ(Solution{}.pushDominoes(".L.R...LR..L.."), "LL.RR.LLRRLL..");
}
}  // unnamed namespace