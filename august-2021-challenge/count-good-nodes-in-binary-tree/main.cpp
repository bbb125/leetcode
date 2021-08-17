#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/615/week-3-august-15th-august-21st/3899/
 * problem:
 * Given a binary tree root, a node X in the tree is named good if in the path
 * from root to X there are no nodes with a value greater than X.
 *
 * Return the number of good nodes in the binary tree.
 *
 * Example 1:
 * Input: root = [3,1,4,3,null,1,5]
 * Output: 4
 * Explanation: Nodes in blue are good.
 * Root Node (3) is always a good node.
 * Node 4 -> (3,4) is the maximum value in the path starting from the root.
 * Node 5 -> (3,4,5) is the maximum value in the path
 * Node 3 -> (3,1,3) is the maximum value in the path.
 *
 * Example 2:
 * Input: root = [3,3,null,4,2]
 * Output: 3
 * Explanation: Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.
 *
 * Example 3:
 * Input: root = [1]
 * Output: 1
 * Explanation: Root is considered as good.
 *
 *
 * Constraints:
 *
 * The number of nodes in the binary tree is in the range [1, 10^5].
 * Each node's value is between [-10^4, 10^4].
 */
namespace
{
struct TreeNode
{
    TreeNode(int x)
        : TreeNode(x, nullptr, nullptr)
    {}
    TreeNode(int x, TreeNode* _left, TreeNode* _right)
        : val{x}
        , left{_left}
        , right{_right}
    {}

    int val         = 0;
    TreeNode* left  = nullptr;
    TreeNode* right = nullptr;
};
class Solution
{
public:
    int goodNodes(TreeNode* root)
    {
        return goodNodesImpl(root, std::numeric_limits<int>::min());
    }
    int goodNodesImpl(TreeNode* root, int max)
    {
        if (!root)
            return 0;
        int newMax = std::max(root->val, max);
        return goodNodesImpl(root->right, newMax)
             + goodNodesImpl(root->left, newMax) + int{newMax == root->val};
    }
};
}  // namespace
namespace
{
TEST(SolutionTests, All)
{
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace