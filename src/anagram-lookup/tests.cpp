#include "AnagramDict.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>

namespace {

//TODO add test fixture with AnagramDict object

TEST(AnagramDict, FindsAllAnagrams) {
    algos::AnagramDict dict;
    dict.insert("God");
    dict.insert("laa");
    dict.insert("odg");
    dict.insert("ala");
    dict.insert("dog");
    //TODO test with (relocated) spaces too
    EXPECT_THROW(
        dict.insert("cccccccaaccaaaaac"),
        std::invalid_argument
    );

    auto [anagramsBegin, anagramsEnd] = dict.findAnagrams("dGO"); //odg
    //ASSERT_NEQ(); //TODO add end() iterator

    EXPECT_EQ(3, std::distance(anagramsBegin, anagramsEnd));

    for (auto it = anagramsBegin; it != anagramsEnd; ++it) {
        //TODO add assertions -- unknown order
        std::cout << it->second << ' ' << it->first << '\n';
    }
}

//TODO test
// DoesNotFindNonAnagrams

} // anonymous namespace
