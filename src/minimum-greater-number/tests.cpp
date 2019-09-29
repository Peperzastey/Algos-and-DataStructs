#include "minGreaterSeq.hpp"
#include <array>
#include <cstdint>
#include <vector>
#include <gtest/gtest.h>

namespace {

TEST(MinGreaterNum, ReturnsFalseIfMGNDoesntExist) {
    {
        std::array<unsigned char, 3> testInput {2, 1, 1};
        auto begin = testInput.begin();
        auto end = testInput.end();

        auto exists = algos::minGreaterSeqInPlace(begin, end);

        EXPECT_EQ(false, exists);
    }
    {
        std::array testInput {1, 1, 1, 1};
        auto begin = testInput.begin();
        auto end = testInput.end();

        auto exists = algos::minGreaterSeqInPlace(begin, end);

        EXPECT_EQ(false, exists);
    }
}

TEST(MinGreaterNum, FindsMGNAndReturnsTrue) {
    {
        using elem_type = std::uint8_t; // same as unsigned char
        std::array<elem_type, 3> testInput {1, 2, 3};
        auto begin = testInput.begin();
        auto end = testInput.end();

        auto exists = algos::minGreaterSeqInPlace(begin, end);

        EXPECT_EQ(true, exists);
        EXPECT_EQ( // promote to a true integral type for proper printing on test failure
            (std::vector<unsigned int>{1, 3, 2}),
            std::vector<unsigned int>(begin, end)
        );
    }
    {
        std::array testInput {5, 7, 3, 1, 4, 3, 2}; // ints
        using elem_type = decltype(testInput)::value_type;
        auto begin = testInput.begin();
        auto end = testInput.end();

        auto exists = algos::minGreaterSeqInPlace(begin, end);

        EXPECT_EQ(true, exists);
        EXPECT_EQ(
            (std::vector<elem_type>{5, 7, 3, 2, 1, 3, 4}),
            std::vector<elem_type>(begin, end)
        );
    }
}

} // anonymous namespace
