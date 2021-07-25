#include <gtest/gtest.h>

#include <random>

/**
 *
 * Given an integer array nums, design an algorithm to randomly shuffle the
 * array. All permutations of the array should be equally likely as a result of
 * the shuffling.
 *
 * Implement the Solution class:
 *
 *     Solution(int[] nums) Initializes the object with the integer array nums.
 * int[] reset() Resets the array to its original configuration and returns it.
 * int[] shuffle() Returns a random shuffling of the array.
 *
 *
 * Example 1:
 *
 * Input
 * ["Solution", "shuffle", "reset", "shuffle"]
 * [[[1, 2, 3]], [], [], []]
 * Output
 * [null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]
 *
 * Explanation
 *     Solution solution = new Solution([1, 2, 3]);
 *     solution.shuffle();    // Shuffle the array [1,2,3] and return its
 * result.
 *     // Any permutation of [1,2,3] must be equally likely to be returned.
 *     // Example: return [3, 1, 2]
 *    solution.reset();      // Resets the array back to its original
 * configuration [1,2,3]. Return [1, 2, 3] solution.shuffle();    // Returns the
 * random shuffling of array [1,2,3]. Example: return [1, 3, 2]
 *
 *
 *
 * Constraints:
 *
 * 1 <= nums.length <= 200
 * -106 <= nums[i] <= 106
 * All the elements of nums are unique.
 * At most 5 * 104 calls in total will be made to reset and shuffle.
 */
class Solution
{
public:
    Solution(std::vector<int> nums)
        : generator_{device_()}
        , nums_{std::move(nums)}
    {}

    /** Resets the array to its original configuration and return it. */
    std::vector<int> reset()
    {
        return nums_;
    }

    /** Returns a random shuffling of the array. */
    std::vector<int> shuffle()
    {
        auto result     = nums_;
        const auto size = std::ssize(nums_);
        for (int i = 0; i < size; ++i)
        {
            auto randomNumber = distribution_(generator_);
            if (randomNumber == 1)
                randomNumber = 0.999999;  // gcc bug
            const int index = (size - i) * randomNumber + i;
            std::swap(result[i], result[index]);
        }
        return result;
    }
    std::random_device device_;
    std::mt19937 generator_;
    std::uniform_real_distribution<double> distribution_{0, 1};
    std::vector<int> nums_;
};

namespace
{
std::vector<int> prepareTestData(std::size_t size)
{
    std::vector<int> result;
    result.reserve(size);
    for (std::size_t i = 0; i < size; ++i)
        result.push_back(i);
    return result;
}

TEST(SolutionTests, All)
{
    constexpr std::size_t size       = 10;
    const auto testData              = prepareTestData(size);
    constexpr std::size_t cycles     = 1000;
    constexpr std::size_t iterations = size * size * cycles;
    auto results                     = std::vector{size, std::vector(size, 0)};
    Solution shuffler{testData};
    for (std::size_t i = 0; i < iterations; ++i)
    {
        auto shuffledVector = shuffler.shuffle();
        for (std::size_t j = 0; j < size; ++j)
            ++results[j][shuffledVector[j]];
    }
    for (auto const& position : results)
    {
        double sum = 0;
        for (std::size_t index = 0; index < size; ++index)
            sum += index * position[index];
        sum /= (size * cycles);
        ASSERT_TRUE(std::abs(sum - size * (size - 1) / 2) < 1);
    }
}
}  // unnamed namespace
