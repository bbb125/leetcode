#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/617/week-5-august-29th-august-31st/3955/
 * problem:
 * Given the root of a binary tree, return true if you can partition the tree
 * into two trees with equal sums of values after removing exactly one edge on
 * the original tree.
 *
 * Example 1:
 * Input: root = [5,10,10,null,null,2,3]
 * Output: true
 *
 * Example 2:
 * Input: root = [1,2,10,null,null,2,20]
 * Output: false
 * Explanation: You cannot split the tree into two trees with equal sums after
 * removing exactly one edge on the tree.
 *
 * Constraints:
 *
 * The number of nodes in the tree is in the range [1, 10^4].
 * -10^5 <= Node.val <= 10^5
 *
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

class Solution
{
public:
    struct Impl
    {
        bool solve(TreeNode* root)
        {
            auto sum = collectSums(root);
            return sum % 2 == 0
                && std::find(std::begin(sums_), std::end(sums_), sum / 2)
                       != std::end(sums_);
        }

        std::int64_t collectSums(TreeNode* root)
        {
            if (!root)
                return 0;
            sums_.push_back(root->val + collectSums(root->left) + collectSums(root->right));
            return sums_.back();
        }

        std::vector<std::int64_t> sums_;
    };
    bool checkEqualTree(TreeNode* root)
    {
        return Impl{}.solve(root);
    }
};
namespace
{
TEST(SolutionTests, All)
{
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace