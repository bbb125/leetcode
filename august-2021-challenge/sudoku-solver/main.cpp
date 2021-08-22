#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <bitset>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/615/week-3-august-15th-august-21st/3905/
 * problem:
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 *
 * A sudoku solution must satisfy all of the following rules:
 *
 * Each of the digits 1-9 must occur exactly once in each row.
 * Each of the digits 1-9 must occur exactly once in each column.
 * Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes
 * of the grid. The '.' character indicates empty cells.
 *
 * Example 1:
 * Input: board =
 * [["5","3",".",".","7",".",".",".","."],
 *  ["6",".",".","1","9","5",".",".","."],
 *  [".","9","8",".",".",".",".","6","."],
 *  ["8",".",".",".","6",".",".",".","3"],
 *  ["4",".",".","8",".","3",".",".","1"],
 *  ["7",".",".",".","2",".",".",".","6"],
 *  [".","6",".",".",".",".","2","8","."],
 *  [".",".",".","4","1","9",".",".","5"],
 *  [".",".",".",".","8",".",".","7","9"]]
 * Output:
 * [["5","3","4","6","7","8","9","1","2"],
 *  ["6","7","2","1","9","5","3","4","8"],
 *  ["1","9","8","3","4","2","5","6","7"],
 *  ["8","5","9","7","6","1","4","2","3"],
 *  ["4","2","6","8","5","3","7","9","1"],
 *  ["7","1","3","9","2","4","8","5","6"],
 *  ["9","6","1","5","3","7","2","8","4"],
 *  ["2","8","7","4","1","9","6","3","5"],
 *  ["3","4","5","2","8","6","1","7","9"]]
 * Explanation: The input board is shown above and the only valid solution is
 * shown below:
 *
 * Constraints:
 *
 * board.length == 9
 * board[i].length == 9
 * board[i][j] is a digit or '.'.
 * It is guaranteed that the input board has only one solution.
 */
// auto update = [](auto& collection, auto index, auto number)
//     {
//     return collection[index].test(number) || !(collection[index][number] = true);
//     };
// for (int i = 0; i < size; ++i)
//{
//     for (int j = 0; j < size; ++j)
//     {
//         if (board[i][j] == '.')
//             continue;
//
//         auto currentNumber       = board[i][j] - '1';
//         const bool invalidSudoku = update(rows, i, currentNumber)
//             || update(cols, j, currentNumber)
//             || update(squares, int(i / 3) * 3 + j / 3, currentNumber);

class Solution
{
public:
    static constexpr auto size = 9;
    using Occurencies          = std::bitset<size>;
    static int squareIndex(int i, int j)
    {
        return int(i / 3) * 3 + j / 3;
    }

    void solveSudoku(std::vector<std::vector<char>>& board)
    {
        board_ = std::move(board);
        initialize();
        solveImpl(0);
        board = std::move(board_);
    }

    bool solveImpl(std::size_t cell)
    {
        if (cell == std::size(missingCells_))
            return true;

        auto myOptions = [&](int i, int j, auto func)
        {
            auto options = rows_[i] | cols_[j] | squares_[squareIndex(i, j)];
            for (int k = 0; k < 9; ++k)
                if (!options.test(k) && func(k))
                        return true;
            return false;
        };

        auto const& currentCell = missingCells_[cell];
        return myOptions(currentCell.i_,
            currentCell.j_,
            [this, &currentCell, cell](auto number)
            {
                board_[currentCell.i_][currentCell.j_] = number + '1';
                setIndexes(currentCell.i_, currentCell.j_);
                if (!solveImpl(cell + 1))
                {
                    resetCell(currentCell.i_, currentCell.j_);
                    return false;
                }
                return true;
            });
    }

    void resetCell(int i, int j)
    {
        auto currentNumber = board_[i][j] - '1';
        auto reset         = [currentNumber](auto& collection, auto index)
        {
            collection[index].reset(currentNumber);
        };
        reset(rows_, i);
        reset(cols_, j);
        reset(squares_, squareIndex(i, j));
        board_[i][j] = '.';
    }

    void setIndexes(int i, int j)
    {
        auto currentNumber = board_[i][j] - '1';
        auto set           = [currentNumber](auto& collection, auto index)
        {
            collection[index].set(currentNumber);
        };
        set(rows_, i);
        set(cols_, j);
        set(squares_, squareIndex(i, j));
    }

    void initialize()
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (board_[i][j] == '.')
                    missingCells_.push_back({i, j});
                else
                    setIndexes(i, j);
            }
        }
    }

    struct MissingCell
    {
        int i_ = 0;
        int j_ = 0;
    };

    bool solved_ = false;
    std::vector<MissingCell> missingCells_;
    std::vector<std::vector<char>> board_;
    std::array<Occurencies, size> rows_;
    std::array<Occurencies, size> cols_;
    std::array<Occurencies, size> squares_;
};

namespace
{
TEST(SolutionTests, All)
{
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace