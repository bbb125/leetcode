#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <bitset>
#include <vector>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/615/week-3-august-15th-august-21st/3904/
 * problem:
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be
 * validated according to the following rules:
 *
 * Each row must contain the digits 1-9 without repetition.
 * Each column must contain the digits 1-9 without repetition.
 * Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
 * Note:
 *
 * A Sudoku board (partially filled) could be valid but is not necessarily solvable.
 * Only the filled cells need to be validated according to the mentioned rules.
 *
 *
 * Example 1:
 * Input: board =
 * [['5','3','.','.','7','.','.','.','.']
 * ,['6','.','.','1','9','5','.','.','.']
 * ,['.','9','8','.','.','.','.','6','.']
 * ,['8','.','.','.','6','.','.','.','3']
 * ,['4','.','.','8','.','3','.','.','1']
 * ,['7','.','.','.','2','.','.','.','6']
 * ,['.','6','.','.','.','.','2','8','.']
 * ,['.','.','.','4','1','9','.','.','5']
 * ,['.','.','.','.','8','.','.','7','9']]
 * Output: true
 *
 *
 * Example 2:
 * Input: board =
 * [['8','3','.','.','7','.','.','.','.']
 * ,['6','.','.','1','9','5','.','.','.']
 * ,['.','9','8','.','.','.','.','6','.']
 * ,['8','.','.','.','6','.','.','.','3']
 * ,['4','.','.','8','.','3','.','.','1']
 * ,['7','.','.','.','2','.','.','.','6']
 * ,['.','6','.','.','.','.','2','8','.']
 * ,['.','.','.','4','1','9','.','.','5']
 * ,['.','.','.','.','8','.','.','7','9']]
 * Output: false
 * Explanation: Same as Example 1, except with the 5 in the top left corner being
 * modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.
 *
 *
 * Constraints:
 *
 * board.length == 9
 * board[i].length == 9
 * board[i][j] is a digit or '.'.
 */

class Solution
{
public:
    bool isValidSudoku(std::vector<std::vector<char>> const& board)
    {
        constexpr auto size = 9;
        using Occurencies   = std::bitset<size>;
        std::array<Occurencies, size> rows;
        std::array<Occurencies, size> cols;
        std::array<Occurencies, size> squares;
        auto update = [](auto& collection, auto index, auto number)
        {
            return collection[index].test(number) || !(collection[index][number] = true);
        };
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (board[i][j] == '.')
                    continue;

                auto currentNumber       = board[i][j] - '1';
                const bool invalidSudoku = update(rows, i, currentNumber)
                                        || update(cols, j, currentNumber)
                                        || update(squares, int(i / 3) * 3 + j / 3, currentNumber);
                if (invalidSudoku)
                    return false;
            }
        }
        return true;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    std::vector<std::vector<char>> example1{//
        std::vector{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        std::vector{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        std::vector{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        std::vector{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        std::vector{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        std::vector{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        std::vector{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        std::vector{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        std::vector{'.', '.', '.', '.', '8', '.', '.', '7', '9'}};  //
    EXPECT_TRUE(Solution{}.isValidSudoku(example1));

    std::vector<std::vector<char>> example2{//
        std::vector{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        std::vector{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        std::vector{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        std::vector{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        std::vector{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        std::vector{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        std::vector{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        std::vector{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        std::vector{'.', '.', '.', '.', '8', '.', '.', '7', '9'}};  //
    EXPECT_FALSE(Solution{}.isValidSudoku(example2));
}
}  // unnamed namespace