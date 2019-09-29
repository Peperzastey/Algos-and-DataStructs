#include "minWindowSubstr.hpp"
#include <array>
#include <vector>
#include <gtest/gtest.h>

namespace {

TEST(MinWindowSubstr, FindsMinSubstrInString) {
    std::string testInput = "abdbaadcbca"; // result: adcb [5-8(inclusive)]
    auto begin = testInput.cbegin();
    auto end = testInput.cend();

    auto [wStart, wEnd, wLength] = algos::minWindowSubstr(begin, end);

    EXPECT_EQ(std::next(begin, 5), wStart);
    EXPECT_EQ(std::next(begin, 9), wEnd);
    EXPECT_EQ(4, wLength);
    //or EXPECT_PRED4
    EXPECT_EQ(
        std::string(std::next(begin, 5), std::next(begin, 9)),
        std::string(wStart, wEnd)
    );
}

TEST(MinWindowSubstr, WorksOnIntegralType) {
    using elem_type = unsigned short;
    std::array<elem_type, 10> testInput {1, 2, 3, 1, 3, 2, 4, 0, 1, 3};
    auto begin = testInput.cbegin();
    auto end = testInput.cend();

    auto [wStart, wEnd, wLength] = algos::minWindowSubstr(begin, end);

    EXPECT_EQ(std::next(begin, 3), wStart);
    EXPECT_EQ(std::next(begin, 8), wEnd);
    EXPECT_EQ(5, wLength);
    EXPECT_EQ(
        std::vector<elem_type>(std::next(begin, 3), std::next(begin, 8)),
        std::vector<elem_type>(wStart, wEnd)
    );
}

TEST(MinWindowSubstr, FindsFirstSubstr) {
    using elem_type = unsigned short;
    std::array<elem_type, 6> testInput {1, 2, 3, 1, 2, 3};
    auto begin = testInput.cbegin();
    auto end = testInput.cend();

    auto [wStart, wEnd, wLength] = algos::minWindowSubstr(begin, end);

    EXPECT_EQ(std::next(begin, 0), wStart);
    EXPECT_EQ(std::next(begin, 3), wEnd);
    EXPECT_EQ(3, wLength);
    EXPECT_EQ(
        std::vector<elem_type>(std::next(begin, 0), std::next(begin, 3)),
        std::vector<elem_type>(wStart, wEnd)
    );
}

TEST(MinWindowSubstr, FindsLastSubstrWhenUsingReverseIterator) {
    using elem_type = unsigned short;
    std::array<elem_type, 8> testInput {1, 1, 2, 1, 3, 1, 2, 3};
    auto begin = testInput.crbegin();
    auto end = testInput.crend();

    auto [wStart, wEnd, wLength] = algos::minWindowSubstr(begin, end);

    EXPECT_EQ(begin, wStart);
    EXPECT_EQ(std::next(begin, 3), wEnd);
    EXPECT_EQ(3, wLength);
    EXPECT_EQ(
        (std::vector<elem_type>{3, 2, 1}),
        std::vector<elem_type>(wStart, wEnd)
    );
}

//test todo
// general value type, including structs/classes/enums
// test iterator category check
// test with reverse iterator

} // anonymous namespace
