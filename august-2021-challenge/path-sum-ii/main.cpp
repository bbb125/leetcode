#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/613/week-1-august-1st-august-7th/3838/
 * problem:
 * Given the root of a binary tree and an integer targetSum, return all
 * root-to-leaf paths where each path's sum equals targetSum.
 * A leaf is a node with no children.
 *
 * Example 1:
 * Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
 * Output: [[5,4,11,2],[5,8,4,5]]
 *
 * Example 2:
 * Input: root = [1,2,3], targetSum = 5
 * Output: []
 *
 * Example 3:
 * Input: root = [1,2], targetSum = 0
 * Output: []
 *
 * Constraints:
 *
 * The number of nodes in the tree is in the range [0, 5000].
 * -1000 <= Node.val <= 1000
 * -1000 <= targetSum <= 1000
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
    using Path   = std::vector<int>;
    using Result = std::vector<Path>;

    Result pathSum(TreeNode* root, int targetSum)
    {
        currentSum_ = targetSum;
        currentPath_.clear();
        pathSumImpl(root);
        return std::move(result_);
    }
    void pathSumImpl(TreeNode* root)
    {
        if (!root)
            return;

        currentSum_ -= root->val;
        currentPath_.push_back(root->val);
        if (currentSum_ == 0 && !root->left && !root->right)
            result_.push_back(currentPath_);
        else
        {
            pathSumImpl(root->left);
            pathSumImpl(root->right);
        }
        currentPath_.pop_back();
        currentSum_ += root->val;
    }
    Path currentPath_;
    int currentSum_ = 0;
    Result result_;
};

namespace
{
TEST(SolutionTests, All)
{
    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace