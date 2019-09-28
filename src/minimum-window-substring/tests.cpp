#include "minWindowSubstr.hpp"
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

//test todo
// general value type, including structs/classes/enums
// test iterator category check
// test with reverse iterator

} // anonymous namespace
