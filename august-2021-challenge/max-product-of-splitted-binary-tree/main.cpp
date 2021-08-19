#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/615/week-3-august-15th-august-21st/3903/
 * problem:
 * Given the root of a binary tree, split the binary tree into two subtrees by
 * removing one edge such that the product of the sums of the subtrees is
 * maximized.
 *
 * Return the maximum product of the sums of the two subtrees. Since the answer
 * may be too large, return it modulo 109 + 7.
 *
 * Note that you need to maximize the answer before taking the mod and not after
 * taking it.
 *
 * Example 1:
 * Input: root = [1,2,3,4,5,6]
 * Output: 110
 * Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10.
 * Their product is 110 (11*10)
 *
 * Example 2:
 * Input: root = [1,null,2,3,4,null,null,5,6]
 * Output: 90
 * Explanation: Remove the red edge and get 2 binary trees with sum 15
 * and 6.Their product is 90 (15*6)
 *
 * Example 3:
 * Input: root = [2,3,9,10,7,8,6,5,4,11,1]
 * Output: 1025
 *
 * Example 4:
 * Input: root = [1,1]
 * Output: 1
 *
 *
 * Constraints:
 * The number of nodes in the tree is in the range [2, 5 * 10^4].
 *
 * 1 <= Node.val <= 10^4
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
        static constexpr auto modulo = static_cast<std::uint64_t>(1e9 + 7);
        int solve(TreeNode* root)
        {
            auto total = collectSums(root);
            if (std::size(sums_) <= 1)
                return 0;

            // max product is achieved when difference between two elements is the smallest
            auto min = *std::min_element(std::begin(sums_),
                std::end(sums_),
                [total](auto left, auto right)
                {
                    auto absVal = [total](auto value)
                    {
                        value *= 2;
                        return std::max(total, value) - std::min(total, value);
                    };
                    return absVal(left) < absVal(right);
                });
            return (std::uint64_t{min % modulo} * ((total - min) % modulo)) % modulo;
        }

        std::uint64_t collectSums(TreeNode* root)
        {
            if (!root)
                return 0;
            sums_.push_back(root->val + collectSums(root->left) + collectSums(root->right));
            return sums_.back();
        }

        std::vector<std::uint64_t> sums_;
    };
    int maxProduct(TreeNode* root)
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