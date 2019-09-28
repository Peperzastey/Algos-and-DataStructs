/** \file
 * \brief Minimum Window Substring implementation.
 */

#ifndef ALGORITHMS_MIN_WINDOW_SUBSTR_HPP_INCLUDED
#define ALGORITHMS_MIN_WINDOW_SUBSTR_HPP_INCLUDED

#include <utility>
#include <iterator>
#include <type_traits>
#include <unordered_map>

/// Algorithms namespace.
namespace algos {

/// Return type of minWindowSubstr() function.
template <typename Iter>
using ReturnType = std::tuple<Iter, Iter, std::size_t>;

/// Find minimum window substring containing all unique elements of the input range.
/**
 * \tparam Iter iterator type, must meet the requirements of LegacyForwardIterator
 * \param first begin iterator of the range
 * \param last end (one-past-last) iterator of the range
 *
 * \return tuple (window-start-iter, window-end-iter, window-length)\n 
 * \a window-end-iter is iterator to one-past-last element of the window
 */
template <typename Iter>
ReturnType<Iter> minWindowSubstr(Iter first, Iter last) {
    static_assert(std::is_base_of_v<std::forward_iterator_tag, typename std::iterator_traits<Iter>::iterator_category>);
    // or is_convertible_v ?

    using value_type = typename std::iterator_traits<Iter>::value_type;
    std::unordered_map<value_type, std::size_t> elementCounts;
    // const iter vs const_iter !
    for (/*const*/auto it = first; it != last; it = std::next(it)) { //TODO std::advance instead of std::next
        elementCounts.try_emplace(*it, 0); //vs. insert({*it, 0})
    }
    std::size_t uniqueElems = elementCounts.size(), elemsPresent = 0;

    Iter wStart, wEnd;
    std::size_t wLength;
    bool initialized = false;
    wStart = wEnd = last;
    wLength = 0;

    Iter currStart = first;  // current start inclusive
    Iter newPos = currStart; // current end inclusive
    for(; newPos != last; newPos = std::next(newPos)) {
        const auto count = ++elementCounts.at(*newPos);
        if (count == 1) {
            ++elemsPresent;
        }
        while (elemsPresent == uniqueElems) {
            std::size_t currLength = std::distance(currStart, newPos) + 1;
            if (currLength < wLength || !initialized) { // found shorter window
                initialized = true;
                wLength = currLength;
                wStart = currStart;
                wEnd = std::next(newPos);
            }

            const auto count = --elementCounts.at(*currStart);
            if (count == 0) {
                --elemsPresent;
            }
            currStart = std::next(currStart);
        }
    }

    return {wStart, wEnd, wLength};
}

//TODO lastMinWindowSubstr()
// easy way: reverse iterator

} // namespace algos

#endif // ALGORITHMS_MIN_WINDOW_SUBSTR_HPP_INCLUDED
