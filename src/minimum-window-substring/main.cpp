#include "minWindowSubstr.hpp"
#include <iostream>
#include <array>

int main() {
    //std::string testInput = "abdbaadcbca"; // result: adcb [5-8(inclusive)]
    //std::string testInput = "abcabcabcbbaacccdab";
    //std::string testInput = "abcb";
    std::array<unsigned short, 10> testInput {1, 2, 3, 1, 3, 2, 4, 0, 1, 3};
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
