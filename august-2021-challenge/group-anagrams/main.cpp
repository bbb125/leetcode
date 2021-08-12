#include <gtest/gtest.h>
#include <gmock/gmock.h>
/**
 * url:
 * https://leetcode.com/explore/challenge/card/august-leetcoding-challenge-2021/614/week-2-august-8th-august-14th/3887/
 * problem:
 * Given an array of strings strs, group the anagrams together. You can return the answer in any order.
 *
 * An Anagram is a word or phrase formed by rearranging the letters of a different
 * word or phrase, typically using all the original letters exactly once.
 *
 * Example 1:
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 *
 * Example 2:
 * Input: strs = [""]
 * Output: [[""]]
 *
 * Example 3:
 * Input: strs = ["a"]
 * Output: [["a"]]
 *
 * Constraints:
 * 1 <= strs.length <= 10^4
 * 0 <= strs[i].length <= 100
 * strs[i] consists of lower-case English letters.
 */
class Solution
{
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
    {
        std::unordered_map<std::string_view, std::vector<std::string>> lookup(std::size(strs));
        for (auto& str : strs)
        {
            std::string copy = str;
            std::sort(std::begin(str), std::end(str));
            lookup[str.c_str()].push_back(std::move(copy));
        }
        std::vector<std::vector<std::string>> result;
        result.reserve(std::size(lookup));
        for (auto& [_, v] : lookup)
            result.push_back(std::move(v));
        return result;
    }
};

/**
 * An interesting solution from comments. I was thinking about generating an integer
 * key, but it would be too big for int. With prime number it's much shorter.
 * primes = {'a': 2,
 *           'b': 3,
 *           'c': 5,
 *           'd': 7,
 *           'e': 11,
 *           'f': 13,
 *           'g': 17,
 *           'h': 19,
 *           'i': 23,
 *           'j': 29,
 *           'k': 31,
 *           'l': 37,
 *           'm': 41,
 *           'n': 43,
 *           'o': 47,
 *           'p': 53,
 *           'q': 59,
 *           'r': 61,
 *           's': 67,
 *           't': 71,
 *           'u': 73,
 *           'v': 79,
 *           'w': 83,
 *           'x': 89,
 *           'y': 97,
 *           'z': 101
 *          }
 *
 *
 *        subLists = {}
 *
 *        for string in strs:
 *            product = 1
 *
 *            for character in string:
 *                product = primes[character] * product
 *
 *            if product in subLists.keys():
 *                listA = subLists[product]
 *                listA.append(string)
 *                subLists[product] = listA
 *            else:
 *                subLists[product] = [string]
 *
 *        listToReturn = []
 *
 *        for value in subLists.keys():
 *            listToReturn.append(subLists[value])
 *
 *        return listToReturn
 */
namespace
{
TEST(SolutionTests, All)
{
    using namespace std::string_literals;
    using namespace ::testing;
    std::vector<std::string> example1{"eat", "tea", "tan", "ate", "nat", "bat"};
    EXPECT_THAT(Solution{}.groupAnagrams(example1),
                UnorderedElementsAre(  //
                    std::vector{"bat"s},
                    UnorderedElementsAreArray({"nat"s, "tan"s}),
                    UnorderedElementsAreArray({"ate"s, "eat"s, "tea"s})));

    std::vector<std::string> example2{""};
    EXPECT_THAT(Solution{}.groupAnagrams(example2),
                UnorderedElementsAre(std::vector{""s}));

    std::vector<std::string> example3{"a"};
    EXPECT_THAT(Solution{}.groupAnagrams(example3),
                UnorderedElementsAre(std::vector{"a"s}));
}
}  // unnamed namespace