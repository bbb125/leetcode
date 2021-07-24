#include <gtest/gtest.h>

#include <deque>
#include <vector>
#include <string>
#include <unordered_set>

/**
 *
 * There is a new alien language that uses the English alphabet. However, the
 * order among the letters is unknown to you.
 *
 * You are given a list of strings words from the alien language's dictionary,
 * where the strings in words are sorted lexicographically by the rules of this
 * new language.
 *
 * Return a string of the unique letters in the new alien language sorted in
 * lexicographically increasing order by the new language's rules. If there is
 * no solution, return "". If there are multiple solutions, return any of them.
 *
 * A string s is lexicographically smaller than a string t if at the first
 * letter where they differ, the letter in s comes before the letter in t in the
 * alien language. If the first min(s.length, t.length) letters are the same,
 * then s is smaller if and only if s.length < t.length.
 *
 *
 *
 * Example 1:
 * Input: words = ["wrt","wrf","er","ett","rftt"]
 * Output: "wertf"
 *
 * Example 2:
 * Input: words = ["z","x"]
 * Output: "zx"
 *
 * Example 3:
 * Input: words = ["z","x","z"]
 * Output: ""
 * Explanation: The order is invalid, so return "".
 *
 *
 * Constraints:
 *
 * 1 <= words.length <= 100
 * 1 <= words[i].length <= 100
 * words[i] consists of only lowercase English letters.
 */

/**
 * Topological sort
 *
 * L ← Empty list that will contain the sorted nodes
 * while exists nodes without a permanent mark do
 * select an unmarked node n
 * visit(n)
 *
 * function visit(node n)
 *      if n has a permanent mark then
 *          return
 *      if n has a temporary mark then
 *          stop   (not a DAG)
 *
 *      mark n with a temporary mark
 *
 *      for each node m with an edge from n to m do
 *          visit(m)
 *
 *      remove temporary mark from n
 *      mark n with a permanent mark
 *      add n to head of L
 */
class Solution
{
public:
    using Connections = std::unordered_map<char, std::unordered_set<char>>;
    using Node        = char;
    using Nodes       = std::unordered_set<char>;

    std::pair<Nodes, Connections> extractConnections(std::vector<std::string> const& words)
    {
        Nodes nodes;
        Connections connections(24);
        const int size = static_cast<int>(words.size());
        for (int i = 0; i < size - 1; ++i)
        {
            auto const& word1 = words[i];
            auto const& word2 = words[i + 1];
            const int length = static_cast<int>(std::min(word1.length(), word2.length()));
            nodes.insert(std::begin(word1), std::end(word1));
            int j = 0;
            for (; j < length && word1[j] == word2[j]; ++j)
                ;
            if (j < length && word1[j] != word2[j])
                connections[word1[j]].insert(word2[j]);
            else if (word1.length() > word2.length() && j == length)
                return {};  // bad data, stupid bug in tests
        }
        nodes.insert(std::begin(words.back()), std::end(words.back()));

        return {std::move(nodes), std::move(connections)};
    }

    std::deque<Node> topologicalSort(Nodes const& nodes, Connections const& connections)
    {
        try
        {
            std::deque<char> result;
            std::unordered_set<char> permanentMark;
            std::array<bool, 26> temporaryMark{};  // BAD: assuming it's char

            std::function<void(char node)> visit;
            visit = [&](Node node)
            {
                if (permanentMark.count(node))
                    return;
                const int nodeIndex = node - 'a';

                if (temporaryMark[nodeIndex])
                    throw std::runtime_error{"DAG"};

                temporaryMark[nodeIndex] = true;

                if (connections.count(node))
                    for (auto const& nodeToCheck : connections.at(node))
                        visit(nodeToCheck);

                temporaryMark[nodeIndex] = false;

                permanentMark.insert(node);
                result.push_front(node);
            };

            while (permanentMark.size() != nodes.size())
            {
                for (auto const& node : nodes)
                    if (!permanentMark.count(node))
                        visit(node);
            }
            return result;
        }
        catch (std::runtime_error const&)
        {
            return {};
        }
    }

    std::string alienOrder(std::vector<std::string> const& words)
    {
        auto [nodes, connections] = extractConnections(words);
        auto sorted               = topologicalSort(nodes, connections);

        return {std::begin(sorted), std::end(sorted)};
    }
};

namespace
{
TEST(SolutionTests, All)
{
    EXPECT_EQ(Solution{}.alienOrder({"wrt", "wrf", "er", "ett", "rftt"}), "wertf");
    EXPECT_EQ(Solution{}.alienOrder({"z", "x"}), "zx");
    EXPECT_EQ(Solution{}.alienOrder({"z", "x", "z"}), "");
    EXPECT_EQ(Solution{}.alienOrder({"z", "z"}), "z");
    EXPECT_EQ(Solution{}.alienOrder({"abc", "ab"}), "");  // bug in tests?
}
}  // unnamed namespace