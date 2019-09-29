#include "minGreaterSeq.hpp"
#include <array>
#include <cstdint>
#include <string>
#include <vector>
#include <gtest/gtest.h>

namespace {

namespace tests_type {    

template <typename T = int>
struct LessComparableType {
    constexpr explicit LessComparableType(const T &val) noexcept
        : val(val) {}
        
    T val;
};

template <typename T>
constexpr inline bool operator<(const LessComparableType<T> &lhs, const LessComparableType<T> &rhs) noexcept {
    return lhs.val < rhs.val;
}

// for unit tests
template <typename T>
constexpr inline bool operator==(const LessComparableType<T> &lhs, const LessComparableType<T> &rhs) noexcept {
    return lhs.val == rhs.val;
}

} // namespace tests_types

TEST(MinGreaterSeqInPlace, ReturnsFalseIfMGSDoesntExist) {
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

TEST(MinGreaterSeqInPlace, FindsMGSAndReturnsTrue) {
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
            (std::array<elem_type, 7>{5, 7, 3, 2, 1, 3, 4}),
            testInput // modified
        );
    }
}

TEST(MinGreaterSeqInPlace, WorksForLessComparableType) {
    using elem_type = tests_type::LessComparableType<int>;
    std::array<elem_type, 3> testInput {
        elem_type{1}, elem_type{3}, elem_type{2}
    };
    auto begin = testInput.begin();
    auto end = testInput.end();

    auto exists = algos::minGreaterSeqInPlace(begin, end);

    EXPECT_EQ(true, exists);
    EXPECT_EQ(
        (std::array{ elem_type{2}, elem_type{1}, elem_type{3} }),
        testInput // modified
    );
}

TEST(MinGreaterSeqInPlace, FindsMGSWhenOneElemToSwap) {
    std::string testInput = "abbbbb"; // ASCII encoding
    auto begin = testInput.begin();
    auto end = testInput.end();

    auto exists = algos::minGreaterSeqInPlace(begin, end);

    EXPECT_EQ(true, exists);
    using namespace std::string_literals;
    EXPECT_EQ(
        "babbbb"s,
        testInput // modified
    );
}

TEST(MinGreaterSeqInPlace, FindsMGSWhenOneElemToSortAfterSwap) {
    std::array testInput {1, 2, 3};
    auto begin = testInput.begin();
    auto end = testInput.end();

    auto exists = algos::minGreaterSeqInPlace(begin, end);

    EXPECT_EQ(true, exists);
    EXPECT_EQ(
        (std::array{1, 3, 2}),
        testInput // modified
    );
}

TEST(MinGreaterSeqInPlace, FindsMGSWhenEvenNumOfElemsToSortAfterSwap) {
    std::array testInput {1, 2, 3, 1, 0, -1}; // 4 elems to sort after swapping 2<->3
    auto begin = testInput.begin();
    auto end = testInput.end();

    auto exists = algos::minGreaterSeqInPlace(begin, end);

    EXPECT_EQ(true, exists);
    EXPECT_EQ(
        (std::array{1, 3, -1, 0, 1, 2}),
        testInput // modified
    );
}

TEST(MinGreaterSeqInPlace, FindsMGSWhenOddNumOfElemsToSortAfterSwap) {
    std::array testInput {1, 2, 3, 1, 0, -1, -2}; // 5 elems to sort after swapping 2<->3
    auto begin = testInput.begin();
    auto end = testInput.end();

    auto exists = algos::minGreaterSeqInPlace(begin, end);

    EXPECT_EQ(true, exists);
    EXPECT_EQ(
        (std::array{1, 3, -2, -1, 0, 1, 2}),
        testInput // modified
    );
}

//TODO test for various types: enums
//TODO test on big input

} // anonymous namespace