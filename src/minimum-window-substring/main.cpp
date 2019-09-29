#include "minWindowSubstr.hpp"
#include <iostream>
#include <array>

//TODO interactive
// exec-name elem-type data
//example: ./mws d 1.1 2.2 1.1 3.3
int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    std::string testInput = "abcabcabcbbaacccdab";
    //std::string testInput = "abcb";
    auto [wStart, wEnd, wLength] = algos::minWindowSubstr(testInput.cbegin(), testInput.cend());

    std::cout << "window length: " << wLength << ", index range: [" << std::distance(testInput.cbegin(), wStart)
        << ',' << std::distance(testInput.cbegin(), wEnd) << "], window: ";
    for (auto it = wStart; it != wEnd; it = std::next(it)) {
        std::cout << *it;
    }
    if (wLength == 0) {
        std::cout << "<not found>";
    }
    std::cout << '\n';
    return 0;
}
