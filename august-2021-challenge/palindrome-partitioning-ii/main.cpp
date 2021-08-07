#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <string_view>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/613/week-1-august-1st-august-7th/3872/
 * problem:
 * Given a string s, partition s such that every substring of the partition is a palindrome.
 *
 * Return the minimum cuts needed for a palindrome partitioning of s.
 *
 * Example 1:
 * Input: s = "aab"
 * Output: 1
 * Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.
 *
 * Example 2:
 * Input: s = "a"
 * Output: 0
 *
 * Example 3:
 * Input: s = "ab"
 * Output: 1
 *
 * Constraints:
 * 1 <= s.length <= 2000
 * s consists of lower-case English letters only.
 */

/**
 * Below are two approaches using memoization technique.
 * The solution is fast enough to be accepted.
 * However, Dynamic Programming approach would work better.
 *
 */
namespace memoization_string_view
{
class Solution
{
public:
    int minCut(std::string s)
    {
        std::string rs{std::rbegin(s), std::rend(s)};
        maxDepth_ = static_cast<int>(std::size(s));
        return minCutImpl(s, rs, 0);
    }
    int minCutImpl(std::string_view str, std::string_view rstr, int depth)
    {
        const auto ssize = std::size(str);
        if (depth > maxDepth_)
            return ssize;
        if (str == rstr)
        {
            maxDepth_ = depth;
            return 0;
        }
        int min = static_cast<int>(ssize);
        for (auto size = static_cast<int>(ssize); size > 0; --size)
        {
            auto part  = str.substr(0, static_cast<std::size_t>(size));
            auto rpart = rstr.substr(static_cast<std::size_t>(ssize - size));
            if (part == rpart)
            {
                auto it = cache_.find(str.substr(static_cast<std::size_t>(size)));
                int partialResult = 0;
                if (it != std::end(cache_))
                    partialResult = it->second;
                else
                {
                    partialResult = minCutImpl(
                        str.substr(static_cast<std::size_t>(size)),
                        rstr.substr(0, static_cast<std::size_t>(ssize - size)),
                        depth + 1);
                    cache_[str.substr(static_cast<std::size_t>(size))] = partialResult;
                }
                min = std::min(partialResult, min);
            }
        }
        return min + 1;
    }
    int maxDepth_ = 2000;
    std::unordered_map<std::string_view, int> cache_;
};
}  // namespace memoization_string_view
namespace memoization_span
{
class Solution
{
public:
    int minCut(std::string s)
    {
        str_      = s;
        int size  = static_cast<int>(std::size(s));
        maxDepth_ = size;
        cache_.resize(size, -1);
        palindromeCache_.resize(size, std::vector<int>(size, -1));
        return minCutImpl(0, 0);
    }
    [[nodiscard]] bool isPalindrome(int left, int right)
    {
        auto& cache = palindromeCache_[left][right];
        if (cache != -1)
            return bool(cache);
        while (left < right)
        {
            if (str_[left] != str_[right])
            {
                cache = false;
                return false;
            }
            ++left;
            --right;
        }
        cache = true;
        return true;
    }
    int minCutImpl(int left, int depth)
    {
        if (cache_[left] != -1)
            return cache_[left];

        if (depth >= maxDepth_)
            return std::size(str_);
        const auto size = static_cast<int>(std::size(str_));
        if (isPalindrome(left, size - 1))
        {
            cache_[left] = 0;
            return 0;
        }

        int min = size - left;
        for (auto leftI = left; leftI < size - 1; ++leftI)
        {
            if (!isPalindrome(left, leftI))
                continue;

            auto partialResult = minCutImpl(leftI + 1, depth + 1);
            min                = std::min(partialResult, min);
        }
        cache_[left] = min + 1;
        return min + 1;
    }
    int maxDepth_ = 0;
    std::string str_;
    std::vector<int> cache_;
    std::vector<std::vector<int>> palindromeCache_;
};
}  // namespace memoization_span

namespace dynamic_programming
{
class Solution
{
public:
    int minCut(std::string)
    {
        return 0;
    }
};
}  // namespace dynamic_programming

namespace
{
TEST(SolutionTests, All)
{
    using namespace memoization_span;
    EXPECT_EQ(2, Solution{}.minCut("leet"));
    EXPECT_EQ(75, Solution{}.minCut("fifgbeajcacehiicccfecbfhhgfiiecdcjjffbghdidbhbdbfbfjccgbbdcjheccfbhafehieabbdfeigbiaggchaeghaijfbjhi"));
    EXPECT_EQ(0, Solution{}.minCut("bb"));
    EXPECT_EQ(1, Solution{}.minCut("aab"));
    EXPECT_EQ(0, Solution{}.minCut("a"));
    EXPECT_EQ(1, Solution{}.minCut("ab"));
}
}  // unnamed namespace