#include <gtest/gtest.h>

#include <string>
#include <functional>
#include <map>
/**
 * Implement the MapSum class:
 *
 *     MapSum() Initializes the MapSum object.
 * void insert(String key, int val) Inserts the key-val pair into the map.
 * If the key already existed, the original key-value pair will be overridden to
 * the new one. int sum(string prefix) Returns the sum of all the pairs' value
 * whose key starts with the prefix.
 *
 *
 * Example 1:
 * Input
 * ["MapSum", "insert", "sum", "insert", "sum"]
 * [[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
 * Output
 * [null, null, 3, null, 5]
 *
 * Explanation
 * MapSum mapSum = new MapSum();
 * mapSum.insert("apple", 3);
 * mapSum.sum("ap");           // return 3 (apple = 3)
 * mapSum.insert("app", 2);
 * mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)
 *
 *
 * Constraints:
 *
 * 1 <= key.length, prefix.length <= 50
 * key and prefix consist of only lowercase English letters.
 * 1 <= val <= 1000
 * At most 50 calls will be made to insert and sum.
 */
namespace
{
constexpr std::size_t maxValues = 26;
std::size_t charHash(char ch)
{
    return ch - 'a';
}

struct Node
{
    using Children = std::array<std::unique_ptr<Node>, 26>;

    int val_ = 0;
    int sum_ = 0;
    Children children_{};
};
class MapSum
{
public:
    MapSum() = default;

    void insert(std::string const& key, int val)
    {
        auto* currentNode = &root_;
        for (auto ch : key)
        {
            auto& newNode = currentNode->children_[charHash(ch)];
            if (!newNode)
                newNode = std::make_unique<Node>();

            currentNode->sum_ += val;
            currentNode = newNode.get();
        }

        if (currentNode->val_ != 0)
        {
            int oldVal        = currentNode->val_;
            currentNode->val_ = 0;
            insert(key, -oldVal);
        }

        currentNode->val_ = val;
    }

    int sum(std::string prefix)
    {
        auto* currentNode = &root_;
        for (auto ch : prefix)
        {
            if (!currentNode)
                return 0;
            currentNode = currentNode->children_[charHash(ch)].get();
        }
        return currentNode->sum_ + currentNode->val_;
    }
    Node root_;
};

}  // namespace

namespace slow_solution
{
namespace
{
bool starts_with(std::string const& left, std::string const& right)
{
    return std::equal(std::begin(left),
                      std::begin(left) + std::min(std::size(left), std::size(right)),
                      std::begin(right));
}
}  // namespace
class MapSum
{
public:
    /** Initialize your data structure here. */
    MapSum() {}

    void insert(std::string key, int val)
    {
        values[key] = val;
    }

    int sum(std::string prefix)
    {
        auto it = values.lower_bound(prefix);
        int sum = 0;
        while (it != std::end(values) && starts_with(prefix, it->first))
        {
            sum += it->second;
            ++it;
        }
        return sum;
    }
    std::map<std::string, int> values;
};
}  // namespace slow_solution

//["MapSum", "insert", "sum", "insert", "sum"]
//[[], ["apple",3], ["apple"], ["app",2], ["ap"]]
namespace
{
TEST(SolutionTests, All)
{
    MapSum solver1;
    solver1.insert("apple", 3);
    EXPECT_EQ(3, solver1.sum("app"));
    solver1.insert("app", 2);
    EXPECT_EQ(5, solver1.sum("ap"));

    MapSum solver2;
    solver2.insert("apple", 3);
    EXPECT_EQ(3, solver2.sum("apple"));
    solver2.insert("app", 2);
    EXPECT_EQ(5, solver2.sum("ap"));

    //    ["MapSum", "insert", "sum", "insert", "sum"]
    //    [[], ["apple",3], ["apple"], ["app",2], ["ap"]]
    //    Output:
    //    [null,null,0,null,5]
    //    Expected:
    //    [null,null,3,null,5]
}
}  // unnamed namespace