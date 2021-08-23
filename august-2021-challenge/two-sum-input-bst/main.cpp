#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/616/week-4-august-22nd-august-28th/3908/
 * problem:
 * Given the root of a Binary Search Tree and a target number k, return true if
 * there exist two elements in the BST such that their sum is equal to the given target.
 *
 * Example 1:
 * Input: root = [5,3,6,2,4,null,7], k = 9
 * Output: true
 *
 * Example 2:
 * Input: root = [5,3,6,2,4,null,7], k = 28
 * Output: false
 *
 * Example 3:
 * Input: root = [2,1,3], k = 4
 * Output: true
 *
 * Example 4:
 * Input: root = [2,1,3], k = 1
 * Output: false
 *
 * Example 5:
 * Input: root = [2,1,3], k = 3
 * Output: true
 *
 * Constraints:
 *
 * The number of nodes in the tree is in the range [1, 10^4].
 * -10^4 <= Node.val <= 10^4
 * root is guaranteed to be a valid binary search tree.
 * -10^5 <= k <= 10^5
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
}  // unnamed namespace
namespace tree_traversing_approach
{
/**
 * Tree traversing approach.
 */
class Solution
{
public:
    bool findTarget(TreeNode* root, int k)
    {
        return nodeExists(root,
            [root, k](auto* node)
            {
                auto* second = find(root, k - node->val);
                return second && second != node;
            });
    }
    template<typename Pred>
    bool nodeExists(TreeNode* root, Pred const& predicate)
    {
        if (!root)
            return false;

        if (predicate(root))
            return true;

        return nodeExists(root->right, predicate) || nodeExists(root->left, predicate);
    }

    static TreeNode* find(TreeNode* root, int k)
    {
        if (!root || root->val == k)
            return root;
        if (root->val > k)
            return find(root->left, k);
        else
            return find(root->right, k);
    }
};
}  // namespace tree_traversing_approach
namespace copy_approach
{
/**
 * copy into vector, and solve the task on an ordered vector.
 * Complexity could be less than implemented. We should look for left range
 * using binary search as well, but it didn't work.
 */
class Solution
{
public:
    bool findTarget(TreeNode* root, int k)
    {
        std::vector<int> orderedValues;
        save(root, orderedValues);
        return solve(orderedValues, k);
    }
    void save(TreeNode* root, std::vector<int>& v)
    {
        if (!root)
            return;

        save(root->left, v);
        v.push_back(root->val);
        save(root->right, v);
    }

    bool solve(std::vector<int> const& v, int target)
    {
        auto left  = std::begin(v);
        auto right = --std::end(v);
        while (left != right)
        {
            right = std::lower_bound(left, right, target - *left);
            if (left == right)
                return false;
            if (*right == target - *left)
                return true;

            ++left;  // = std::lower_bound(left, right - 1, target - *right);
        }
        return false;
    }
};
}  // namespace copy_approach
namespace
{
TEST(SolutionTests, All)
{
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace