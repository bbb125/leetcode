#include <gtest/gtest.h>

#include <vector>
#include <numeric>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/613/week-1-august-1st-august-7th/3834/
 * problem:
 * There are n houses in a village. We want to supply water for all the houses
 * by building wells and laying pipes.
 *
 * For each house i, we can either build a well inside it directly with cost
 * wells[i
 * - 1] (note the -1 due to 0-indexing), or pipe in water from another well to
 * it. The costs to lay pipes between houses are given by the array pipes, where
 * each pipes[j] = [house1j, house2j, costj] represents the cost to connect
 * house1j and house2j together using a pipe. Connections are bidirectional.
 *
 * Return the minimum total cost to supply water to all houses.
 *
 * Example 1:
 * Input: n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]]
 * Output: 3
 * Explanation:
 * The image shows the costs of connecting houses using pipes.
 * The best strategy is to build a well in the first house with cost 1 and
 * connect the other houses to it with cost 2 so the total cost is 3.
 *
 *
 * Constraints:
 *
 * 1 <= n <= 104
 * wells.length == n
 * 0 <= wells[i] <= 105
 * 1 <= pipes.length <= 104
 * pipes[j].length == 3
 * 1 <= house1j, house2j <= n
 * 0 <= costj <= 105
 * house1j != house2j
 */
class Solution
{
public:
    int minCostToSupplyWater(int n,
        std::vector<int> const& wells,
        std::vector<std::vector<int>> const& pipes)
    {
        struct Edge
        {
            int from   = 0;
            int to     = 0;
            int weight = 0;
        };
        std::vector<int> nodes(n + 1);
        std::iota(std::begin(nodes), std::end(nodes), 0);

        auto findRoot = [&nodes](int node)
        {
            while (nodes[node] != node)
            {
                nodes[node] = nodes[nodes[node]];
                node        = nodes[node];
            }
            return node;
        };

        auto combine = [&](int node1, int node2)
        {
            int root1    = findRoot(node1);
            int root2    = findRoot(node2);
            nodes[root1] = nodes[root2];
        };

        const int wellsSize = static_cast<int>(std::size(wells));
        const int pipesSize = static_cast<int>(std::size(pipes));
        const int edgesSize = wellsSize + pipesSize;
        const auto edges    = [&]
        {
            std::vector<Edge> result;
            result.reserve(edgesSize);

            for (int i = 0; i < wellsSize; ++i)
                result.push_back({0, i + 1, wells[i]});

            for (int i = 0; i < pipesSize; ++i)
                result.push_back({pipes[i][0], pipes[i][1], pipes[i][2]});

            std::sort(  // no-format
                std::begin(result),
                std::end(result),
                [](auto const& left, auto const& right)
                {
                    return left.weight < right.weight;
                });
            return result;
        }();

        int result                = 0;
        int numberOfIncludedNodes = 0;

        for (auto const& edge : edges)
        {
            const int fromRoot = findRoot(edge.from);
            const int toRoot   = findRoot(edge.to);
            if (fromRoot != toRoot)
            {
                result += edge.weight;
                combine(fromRoot, toRoot);

                ++numberOfIncludedNodes;
                if (numberOfIncludedNodes == n)
                    return result;
            }
        }
        return result;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(167061,
        Solution{}.minCostToSupplyWater(  // no-format
            7,
            {14545, 18504, 48032, 46725, 76232, 50574, 12109},
            {std::vector{3, 1, 83424},
                std::vector{4, 3, 12977},
                std::vector{5, 1, 48398},
                std::vector{6, 3, 99185},
                std::vector{7, 4, 9954}}));
    //    6
    //    [4625,65696,86292,68291,37147,7880]
    //    [[2,1,79394],[3,1,45649],[4,1,75810],[5,3,22340],[6,1,6222]]
    EXPECT_EQ(204321,
        Solution{}.minCostToSupplyWater(  // no-format
            6,
            {4625, 65696, 86292, 68291, 37147, 7880},
            {std::vector{2, 1, 79394},
                std::vector{3, 1, 45649},
                std::vector{4, 1, 75810},
                std::vector{5, 3, 22340},
                std::vector{6, 1, 6222}}));
    EXPECT_EQ(3,
        Solution{}.minCostToSupplyWater(3,
            {1, 2, 2},
            {std::vector{1, 2, 1}, std::vector{2, 3, 1}}));

    EXPECT_EQ(2032576,
        Solution{}.minCostToSupplyWater(  // no-format
            60,
            {93151,
                20876,
                59743,
                57253,
                22852,
                68389,
                7424,
                54743,
                32955,
                39509,
                14896,
                54179,
                51356,
                78618,
                95595,
                69161,
                37790,
                67284,
                91644,
                91111,
                52096,
                61039,
                56597,
                70549,
                72491,
                90473,
                42299,
                76091,
                89905,
                31271,
                58546,
                48511,
                72171,
                78695,
                41038,
                81168,
                32922,
                49332,
                637,
                7340,
                70333,
                20202,
                45698,
                64674,
                12549,
                46263,
                26798,
                1334,
                30355,
                83189,
                26439,
                51031,
                85145,
                56095,
                38430,
                79718,
                82385,
                25719,
                97525,
                82106},
            {std::vector{2, 1, 21154},
                std::vector{3, 2, 81115},
                std::vector{4, 3, 94841},
                std::vector{5, 2, 96414},
                std::vector{6, 3, 72515},
                std::vector{7, 5, 52265},
                std::vector{8, 1, 60281},
                std::vector{9, 5, 47008},
                std::vector{10, 6, 83062},
                std::vector{11, 1, 83592},
                std::vector{12, 11, 29667},
                std::vector{13, 5, 43482},
                std::vector{14, 8, 68029},
                std::vector{15, 6, 29058},
                std::vector{16, 14, 14198},
                std::vector{17, 8, 61513},
                std::vector{18, 10, 96383},
                std::vector{19, 3, 12103},
                std::vector{21, 11, 51835},
                std::vector{22, 8, 14803},
                std::vector{23, 22, 30324},
                std::vector{24, 23, 63187},
                std::vector{25, 21, 62508},
                std::vector{26, 13, 86421},
                std::vector{27, 22, 59810},
                std::vector{28, 6, 80818},
                std::vector{29, 25, 350},
                std::vector{30, 26, 9676},
                std::vector{31, 27, 11396},
                std::vector{33, 29, 39112},
                std::vector{34, 18, 35099},
                std::vector{35, 3, 79588},
                std::vector{36, 25, 93238},
                std::vector{37, 30, 18366},
                std::vector{38, 16, 57918},
                std::vector{39, 36, 14416},
                std::vector{40, 25, 27362},
                std::vector{41, 5, 12434},
                std::vector{42, 9, 5570},
                std::vector{43, 42, 72309},
                std::vector{44, 8, 81276},
                std::vector{45, 44, 2620},
                std::vector{46, 44, 57766},
                std::vector{47, 11, 71293},
                std::vector{48, 40, 14627},
                std::vector{49, 48, 33901},
                std::vector{52, 49, 70471},
                std::vector{53, 38, 6615},
                std::vector{55, 19, 77453},
                std::vector{56, 9, 63999},
                std::vector{57, 34, 10940},
                std::vector{58, 29, 43449},
                std::vector{59, 43, 22295},
                std::vector{60, 5, 84242}}));
}
}  // unnamed namespace