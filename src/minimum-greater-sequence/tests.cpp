#include "minGreaterSeq.hpp"
#include <array>
#include <cstdint>
#include <forward_list>
#include <list>
#include <string>
#include <vector>
#include <gtest/gtest.h>

namespace {

namespace tests_type {    

template <typename T = int>
struct LessThanComparableType {
    constexpr explicit LessThanComparableType(const T &val) noexcept
        : val(val) {}

    T val;
};

template <typename T>
constexpr inline bool operator<(const LessThanComparableType<T> &lhs, const LessThanComparableType<T> &rhs) noexcept {
    return lhs.val < rhs.val;
}

// for unit tests
template <typename T>
constexpr inline bool operator==(const LessThanComparableType<T> &lhs, const LessThanComparableType<T> &rhs) noexcept {
    return lhs.val == rhs.val;
}

} // namespace tests_types

TEST(MinGreaterSeqInPlace, ReturnsFalseForEmptySeq) {
    std::array<int, 0> testInput {};
    auto begin = testInput.begin();
    auto end = testInput.end();

    auto exists = algos::minGreaterSeqInPlace(begin, end);

    EXPECT_EQ(false, exists);
}

TEST(MinGreaterSeqInPlace, ReturnsFalseForSingleElemSeq) {
    std::array testInput {-300};
    auto begin = testInput.begin();
    auto end = testInput.end();

    auto exists = algos::minGreaterSeqInPlace(begin, end);

    EXPECT_EQ(false, exists);
}

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

//TODO gtest parameterized test
TEST(MinGreaterSeqInPlace, WhenReturnsFalseSeqIsNotModified) {
    {
        using elem_type = std::uint8_t;
        std::array<elem_type, 3> testInput {2, 1, 1};
        auto begin = testInput.begin();
        auto end = testInput.end();

        auto exists = algos::minGreaterSeqInPlace(begin, end);

        ASSERT_EQ(false, exists);
        EXPECT_EQ(
            (std::array<elem_type, 3>{2, 1, 1}),
            testInput
        );
    }
    {
        std::array testInput {1, 1, 1, 1};
        auto begin = testInput.begin();
        auto end = testInput.end();

        auto exists = algos::minGreaterSeqInPlace(begin, end);

        ASSERT_EQ(false, exists);
        EXPECT_EQ(
            (std::array{1, 1, 1, 1}),
            testInput
        );
    }
    {
        std::array<int, 0> testInput {};
        auto begin = testInput.begin();
        auto end = testInput.end();

        auto exists = algos::minGreaterSeqInPlace(begin, end);

        ASSERT_EQ(false, exists);
        EXPECT_EQ(
            (std::array<int, 0>{}),
            testInput
        );
    }
    {
        std::array testInput {-300};
        auto begin = testInput.begin();
        auto end = testInput.end();

        auto exists = algos::minGreaterSeqInPlace(begin, end);

        ASSERT_EQ(false, exists);
        EXPECT_EQ(
            (std::array{-300}),
            testInput
        );
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

TEST(MinGreaterSeqInPlace, WorksForLessThanComparableType) {
    using elem_type = tests_type::LessThanComparableType<int>;
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

TEST(MinGreaterSeqInPlace, WorksForRandomAccessIterator) {
    {
        std::array testInput {1, 2, 3, 1, 0, -1, -2};
        auto begin = testInput.begin();
        auto end = testInput.end();

        auto exists = algos::minGreaterSeqInPlace(begin, end);

        EXPECT_EQ(true, exists);
        EXPECT_EQ(
            (std::array{1, 3, -2, -1, 0, 1, 2}),
            testInput // modified
        );
    }
    {
        std::vector testInput {1, 2, 3, 1, 0, -1, -2};
        auto begin = testInput.begin();
        auto end = testInput.end();

        auto exists = algos::minGreaterSeqInPlace(begin, end);

        EXPECT_EQ(true, exists);
        EXPECT_EQ(
            (std::vector{1, 3, -2, -1, 0, 1, 2}),
            testInput // modified
        );
    }
}

TEST(MinGreaterSeqInPlace, WorksForBidirIterator) {
    std::list testInput {1, 2, 3, 1, 0, -1, -2};
    auto begin = testInput.begin();
    auto end = testInput.end();

    auto exists = algos::minGreaterSeqInPlace(begin, end);

    EXPECT_EQ(true, exists);
    EXPECT_EQ(
        (std::list{1, 3, -2, -1, 0, 1, 2}),
        testInput // modified
    );
}

//TODO cmake's try_compile for static_asserts + check compiler error: "static assertion failed"
// should not compile
/*TEST(MinGreaterSeqInPlace, DoesntWorkForForwardIterator) {
    std::forward_list testInput {1, 2, 3, 1, 0, -1, -2};
    auto begin = testInput.begin();
    auto end = testInput.end();

    auto exists = algos::minGreaterSeqInPlace(begin, end);

    EXPECT_EQ(true, exists);
    EXPECT_EQ(
        (std::list{1, 3, -2, -1, 0, 1, 2}),
        testInput // modified
    );
}*/

//TODO add test for reverse iterators (reverse sequence) [STL-compliance]
//TODO add test for std::begin, std::end C-array specialization
//TODO add test using raw pointer as iterator (random access iterator)
    //e.g.: algos::minGreaterSeqInPlace(carray, carray + (sizeof carray / sizeof carray[0]))
//TODO add test for std::map (unordered) with swap specialization for value_type (key:=position in seq)
//TODO add test for carray as value_type (e.g. vector of arrays)
//TODO add test for std::unique_ptr as value_type

//TODO types with working std::next(it) but not ++it
//TODO tests for stable-swaps <-- need an impl with stable sort (e.g. insertion sort) -- std::stable_sort
//TODO test for various types: enums, does not for scoped enums (non-comparable (?))
//TODO test on big input

} // anonymous namespace
