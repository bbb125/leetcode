#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/613/week-1-august-1st-august-7th/3871/
 * problem:
 * Given an n-ary tree, return the level order traversal of its nodes' values.
 *
 * Nary-Tree input serialization is represented in their level order traversal,
 * each group of children is separated by the null value (See examples).
 *
 * Example 1:
 * Input: root = [1,null,3,2,4,null,5,6]
 * Output: [[1],[3,2,4],[5,6]]
 *
 * Example 2:
 * Input: root =
 * [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
 * Output: [[1],[2,3,4,5],[6,7,8,9,10],[11,12,13],[14]]
 *
 *
 * Constraints:
 *
 * The height of the n-ary tree is less than or equal to 1000
 * The total number of nodes is between [0, 10^4]
 */
namespace
{
struct Node
{
    Node(int _val)
        : Node{_val, {}}
    {}

    Node(int _val, std::vector<Node*> _children)
        : val{_val}
        , children{std::move(_children)}
    {}

    int val = 0;
    std::vector<Node*> children;

};
}  // unnamed namespace
class Solution
{
public:
    std::vector<std::vector<int>> levelOrder(Node* root)
    {
        if (!root)
            return {};
        std::vector<std::vector<int>> result;
        std::vector<Node*> currentRow{root};
        std::vector<Node*> nextRow;
        while (!currentRow.empty())
        {
            std::vector<int> resultRow;
            resultRow.reserve(std::size(currentRow));
            for (auto *node: currentRow)
            {
                for (auto *child: node->children)
                    nextRow.push_back(child);
                resultRow.push_back(node->val);
            }

            result.emplace_back(std::move(resultRow));
            currentRow = std::move(nextRow);
        }
        return result;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace