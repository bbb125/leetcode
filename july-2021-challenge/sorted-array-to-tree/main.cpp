#include <gtest/gtest.h>

#include <vector>
/**
 * Given an integer array nums where the elements are sorted in ascending order,
 * convert it to a height-balanced binary search tree.
 *
 * A height-balanced binary tree is a binary tree in which the depth of the two
 * subtrees of every node never differs by more than one.
 *
 * Example 1:
 * Input: nums = [-10,-3,0,5,9]
 * Output: [0,-3,9,-10,null,5]
 * Explanation: [0,-10,5,null,-3,null,9] is also accepted:
 *
 * Example 2:
 * Input: nums = [1,3]
 * Output: [3,1]
 * Explanation: [1,3] and [3,1] are both a height-balanced BSTs.
 *
 *
 * Constraints:
 *
 * 1 <= nums.length <= 104
 * -104 <= nums[i] <= 104
 * nums is sorted in a strictly increasing order.
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
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
    TreeNode* buildTree(int left, int right, std::vector<int> const& nums)
    {
        if (left > right)
            return nullptr;

        const int mid   = (right + left) / 2;
        auto* leftTree  = buildTree(left, mid - 1, nums);
        auto* rightTree = buildTree(mid + 1, right, nums);
        auto* root      = new TreeNode{nums[mid], leftTree, rightTree};
        return root;
    }
    TreeNode* sortedArrayToBST(std::vector<int>& nums)
    {
        return buildTree(0, std::ssize(nums) - 1, nums);
    }
};

namespace
{
TEST(SolutionTests, All)
{
    ;
}
}  // namespace