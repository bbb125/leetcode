#include <gtest/gtest.h>
#include <vector>

/**
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
 *
 * The distance between two adjacent cells is 1.
 *
 * Example 1:
 * Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
 * Output: [[0,0,0],[0,1,0],[0,0,0]]
 *
 * Example 2:
 * Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
 * Output: [[0,0,0],[0,1,0],[1,2,1]]
 *
 * Constraints:
 *
 * m == mat.length
 * n == mat[i].length
 * 1 <= m, n <= 104
 * 1 <= m * n <= 104
 * mat[i][j] is either 0 or 1.
 * There is at least one 0 in mat.
 */
namespace
{
using Matrix = std::vector<std::vector<int>>;
template<typename Container>
int ssize(Container const& container)
{
    return static_cast<int>(std::size(container));
}

int safeAt(Matrix const& matrix, int i, int j)
{
    return (i >= 0 && j >= 0 && i < ssize(matrix) && j < ssize(matrix.front()))
             ? matrix[i][j]
             : ssize(matrix) * ssize(matrix.front());
}
}  // unnamed namespace
class Solution
{
public:
    Matrix updateMatrix(Matrix& matrix)
    {
        const int M = ssize(matrix);
        const int N = ssize(matrix.front());

        Matrix result(M, std::vector(N, M * N));
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
                result[i][j] = matrix[i][j] == 0  //
                                 ? 0
                                 : std::min(safeAt(result, i - 1, j),
                                            safeAt(result, i, j - 1))
                                       + 1;
        }

        for (int i = M - 1; i >= 0; --i)
        {
            for (int j = N - 1; j >= 0; --j)
                result[i][j] = matrix[i][j] == 0  //
                                 ? 0
                                 : std::min(result[i][j],
                                            std::min(safeAt(result, i + 1, j),
                                                     safeAt(result, i, j + 1))
                                                + 1);
        }

        return result;
    }
};

namespace
{
TEST(SolutionTests, All)
{
    //    Solution{}.[[0,0,0],[0,1,0],[1,1,1]]
    // Output: [[0,0,0],[0,1,0],[1,2,1]]

//Input:
//    [[0,1,0,1,1],
//     [1,1,0,0,1],
//     [0,0,0,1,0],
//     [1,0,1,1,1],
//     [1,0,0,0,1]]
//Output:
//    [[0,1,0,1,2],
//     [1,2,0,0,1],
//     [0,0,0,1,0],
//     [1,0,1,2,1],
//     [2,0,0,0,1]]
//Expected:
//    [[0,1,0,1,2],
//     [1,1,0,0,1],
//     [0,0,0,1,0],[1,0,1,1,1],[1,0,0,0,1]]
}
}  // namespace