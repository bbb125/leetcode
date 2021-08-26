#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stack>
#include <string>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/616/week-4-august-22nd-august-28th/3920/
 * problem:
 * One way to serialize a binary tree is to use preorder traversal. When we
 * encounter a non-null node, we record the node's value. If it is a null node,
 * we record using a sentinel value such as '#'.
 *
 * For example, the above binary tree can be serialized to the string
 * "9,3,4,#,#,1,#,#,2,#,6,#,#", where '#' represents a null node.
 *
 * Given a string of comma-separated values preorder, return true if it is a
 * correct preorder traversal serialization of a binary tree.
 *
 * It is guaranteed that each comma-separated value in the string must be either
 * an integer or a character '#' representing null pointer.
 *
 * You may assume that the input format is always valid.
 *
 * For example, it could never contain two consecutive commas, such as "1,,3".
 * Note: You are not allowed to reconstruct the tree.
 *
 * Example 1:
 * Input: preorder = "9,3,4,#,#,1,#,#,2,#,6,#,#"
 * Output: true
 *
 * Example 2:
 * Input: preorder = "1,#"
 * Output: false
 *
 * Example 3:
 * Input: preorder = "9,#,#,1"
 * Output: false
 *
 * Constraints:
 *
 * 1 <= preorder.length <= 10^4
 * preoder consist of integers in the range [0, 100] and '#' separated by commas
 * ','.
 */
namespace stack
{
class Solution
{
public:
    bool isValidSerialization(std::string preorder)
    {
        // 9,3,4,#,#,1,#,#,2,#,6,#,#
        //
        std::stringstream stream{preorder};
        std::stack<int> nodes;
        std::string item;
        bool treeFinished = false;
        while (std::getline(stream, item, ','))
        {
            if (treeFinished)
                return false;

            if (!nodes.empty())
                ++nodes.top();

            if (item != "#")
                nodes.push(0);

            while (!nodes.empty() && nodes.top() == 2)
                nodes.pop();
            if (nodes.empty())
                treeFinished = true;
        }
        return nodes.empty() && treeFinished;
    }
};
}  // namespace stack
class Solution
{
public:
    bool isValidSerialization(std::string preorder)
    {
        std::stringstream stream{preorder};
        std::string item;
        int slots = 1;
        while (std::getline(stream, item, ','))
        {
            --slots;
            if (slots < 0)
                return false;
            if (item != "#")
                slots += 2;
        }
        return slots == 0;
    }
};
namespace
{
TEST(SolutionTests, All)
{
    EXPECT_TRUE(Solution{}.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#"));
    EXPECT_FALSE(Solution{}.isValidSerialization("1,#"));
    EXPECT_FALSE(Solution{}.isValidSerialization("1,#,#,#"));
    EXPECT_TRUE(Solution{}.isValidSerialization("#"));
    EXPECT_FALSE(Solution{}.isValidSerialization("9,#,#,1"));

    // EXPECT_THAT(Solution{}.twoSum(example2, 6), ::testing::UnorderedElementsAre(1, 2));
}
}  // unnamed namespace