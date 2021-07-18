#include <gtest/gtest.h>

/**
 * Given a linked list, reverse the nodes of a linked list k at a time and
 * return its modified list.
 *
 * k is a positive integer and is less than or equal to the length of the linked
 * list. If the number of nodes is not a multiple of k then left-out nodes, in
 * the end, should remain as it is.
 *
 * You may not alter the values in the list's nodes, only nodes themselves may
 * be changed.
 *
 * Example 1:
 * Input: head = [1,2,3,4,5], k = 2
 * Output: [2,1,4,3,5]
 *
 * Example 2:
 * Input: head = [1,2,3,4,5], k = 3
 * Output: [3,2,1,4,5]
 *
 * Example 3:
 * Input: head = [1,2,3,4,5], k = 1
 * Output: [1,2,3,4,5]
 *
 * Example 4:
 * Input: head = [1], k = 1
 * Output: [1]
 *
 *
 * Constraints:
 *
 * The number of nodes in the list is in the range sz.
 * 1 <= sz <= 5000
 * 0 <= Node.val <= 1000
 * 1 <= k <= sz
 *
 *
 *     Follow-up: Can you solve the problem in O(1) extra memory space?
 */

namespace
{
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode
{
    ListNode()
        : ListNode{0, nullptr}
    {}

    ListNode(int x)
        : ListNode{x, nullptr}
    {}

    ListNode(int x, ListNode* next)
        : val{x}
        , next{next}
    {}
    int val        = 0;
    ListNode* next = nullptr;
};

template<typename Range>
ListNode* makeList(Range&& range)
{
    ListNode* current = nullptr;
    for (auto it = std::rbegin(range); it != std::rend(range); ++it)
        current = new ListNode{*it, current};

    return current;
}

template<typename Range>
ListNode* firstNotEqual(ListNode* listHead, Range const& range)
{
    auto it       = std::begin(range);
    auto rangeEnd = std::end(range);
    auto* current = listHead;
    while (it != rangeEnd && current != nullptr && current->val == *it)
    {
        ++it;
        current = current->next;
    }
    return current;
}
}  // namespace

class Solution
{
public:
    struct ReverseGroupResult
    {
        ListNode* groupFirst_ = nullptr;
        ListNode* groupLast_  = nullptr;
        ListNode* listHead_   = nullptr;
        bool completed_       = false;
    };
    ReverseGroupResult reverseOneGroup(ListNode* head, int k)
    {
        ListNode* groupStart = nullptr;
        ListNode* current    = head;
        while (current != nullptr && k > 0)
        {
            auto* next = current;
            current    = next->next;
            next->next = groupStart;
            groupStart = next;
            --k;
        }
        return {groupStart, head, current, k == 0};
    }
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        ListNode* newListStart = nullptr;
        ListNode* lastGroupEnd = nullptr;

        while (head != nullptr)
        {
            auto reverseResult = reverseOneGroup(head, k);
            if (!reverseResult.completed_)  // reverse one more time if we couldn't complete it
                reverseResult = reverseOneGroup(reverseResult.groupFirst_, k);

            // either initialize new first element or attach list
            if (newListStart == nullptr) [[unlikely]]
                newListStart =  reverseResult.groupFirst_;
            else
                lastGroupEnd->next = reverseResult.groupFirst_;

            lastGroupEnd = reverseResult.groupLast_;
            head         = reverseResult.listHead_;
        }
        return newListStart;
    }
};

namespace
{
TEST(SolutionTests, All)
{
    /**
     * Example 1:
     * Input: head = [1,2,3,4,5], k = 2
     * Output: [2,1,4,3,5]
     */
    EXPECT_EQ(nullptr,
              firstNotEqual(Solution{}.reverseKGroup(makeList(std::vector{1, 2, 3, 4, 5}), 2),
                            std::vector{2, 1, 4, 3, 5}));
    /**
     * Example 2:
     * Input: head = [1,2,3,4,5], k = 3
     * Output: [3,2,1,4,5]
     */
    EXPECT_EQ(nullptr,
              firstNotEqual(Solution{}.reverseKGroup(makeList(std::vector{1, 2, 3, 4, 5}), 3),
                            std::vector{3, 2, 1, 4, 5}));
    /**
     * Example 3:
     * Input: head = [1,2,3,4,5], k = 1
     * Output: [1,2,3,4,5]
     */
    EXPECT_EQ(nullptr,
              firstNotEqual(Solution{}.reverseKGroup(makeList(std::vector{1, 2, 3, 4, 5}), 1),
                            std::vector{1, 2, 3, 4, 5}));
    /**
     * Example 4:
     * Input: head = [1], k = 1
     * Output: [1]
     */
    EXPECT_EQ(nullptr,
              firstNotEqual(Solution{}.reverseKGroup(makeList(std::vector{1}), 1),
                            std::vector{1}));
}
}  // unnamed namespace