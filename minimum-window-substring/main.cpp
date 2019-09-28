#include <iostream>
#include <utility>

template <typename Iter>
std::pair<Iter, Iter> minWindowSubstr(Iter start, Iter end) {
    return {end, end};
}

int main() {
    std::string testInput = "abdbaadcbca"; // result: adcb [5-8]
    auto [wStart, wEnd] = minWindowSubstr(testInput.cbegin(), testInput.cend());
    for (auto it = wStart; it != wEnd; it = std::next(it)) {
        std::cout << *it;
    }
    std::cout << '\n' << "index range: [" << std::distance(testInput.cbegin(), wStart)
        << ',' << std::distance(testInput.cbegin(), wEnd) << "]\n";
    return 0;
}
