#include <gtest/gtest.h>
#include <algorithm>
/*
 * Given the root of a binary tree, return the length of the longest consecutive
 * path in the tree.
 *
 * This path can be either increasing or decreasing.
 *
 * For example, [1,2,3,4] and [4,3,2,1] are both considered valid, but the path
 * [1,2,4,3] is not valid. On the other hand, the path can be in the
 * child-Parent-child order, where not necessarily be parent-child order.
 *
 * Example 1:
 * Input: root = [1,2,3]
 * Output: 2
 * Explanation: The longest consecutive path is [1, 2] or [2, 1].
 *
 * Example 2:
 * Input: root = [2,1,3]
 * Output: 3
 * Explanation: The longest consecutive path is [1, 2, 3] or [3, 2, 1].
 *
 *
 * Constraints:
 * The number of nodes in the tree is in the range [1, 3 * 104].
 * -3 * 104 <= Node.val <= 3 * 104
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
    struct Result
    {
        int asc_  = 1;
        int desc_ = 1;
    };
    int solution_ = 0;
    Result solve(TreeNode* root)
    {
        auto process = [this](auto* node, int value) -> Result
        {
          if (!node)
              return {};

          auto result = solve(node);
          result.asc_ = int{value == node->val + 1} * result.asc_ + 1;
          result.desc_ = int{value == node->val - 1} * result.desc_ + 1;
          return result;
        };
        auto rightResult = process(root->right, root->val);
        auto leftResult  = process(root->left, root->val);
        Result result{std::max(rightResult.asc_, leftResult.asc_),
                      std::max(rightResult.desc_, leftResult.desc_)};
        solution_ = std::max(solution_, result.desc_ + result.asc_ - 1);
        return result;
    }

    int longestConsecutive(TreeNode* root)
    {
        solve(root);
        return solution_;
    }
};

namespace
{
TEST(SolutionTests, All) {}
}  // unnamed namespace