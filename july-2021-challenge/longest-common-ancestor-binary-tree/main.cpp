#include <gtest/gtest.h>

/**
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) of
 * two given nodes in the BST.
 *
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor
 * is defined between two nodes p and q as the lowest node in T that has both p
 * and q as descendants (where we allow a node to be a descendant of itself).”
 *
 * Example 1:
 * Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
 * Output: 6
 * Explanation: The LCA of nodes 2 and 8 is 6.
 *
 * Example 2:
 * Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
 * Output: 2
 * Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant
 * of itself according to the LCA definition.
 *
 * Example 3:
 * Input: root = [2,1], p = 2, q = 1
 * Output: 2
 *
 *
 * Constraints:
 *
 * The number of nodes in the tree is in the range [2, 105].
 * -109 <= Node.val <= 109
 * All Node.val are unique.
 * p != q
 * p and q will exist in the BST.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
namespace
{
struct TreeNode
{
    TreeNode(int x)
        : val{x}
    {}

    int val         = 0;
    TreeNode* left  = nullptr;
    TreeNode* right = nullptr;
};

}  // unnamed namespace
class Solution
{
public:
    using NodesStack = std::vector<TreeNode*>;
    NodesStack find(TreeNode* root, int value)
    {
        NodesStack stack;
        while (root->val != value)
        {
            stack.push_back(root);
            if (value < root->val)
                root = root->left;
            else
                root = root->right;
        }
        stack.push_back(root);
        return stack;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        auto pNodes   = find(root, p->val);
        auto qNodes   = find(root, q->val);
        auto pNodesIt = std::begin(pNodes);
        auto qNodesIt = std::begin(qNodes);
        while (pNodesIt != std::end(pNodes) && qNodesIt != std::end(qNodes)
               && *pNodesIt == *qNodesIt)
        {
            ++pNodesIt;
            ++qNodesIt;
        }
        return *--pNodesIt;
    }
};
namespace
{
TEST(SolutionTests, All) {}
}  // unnamed namespace