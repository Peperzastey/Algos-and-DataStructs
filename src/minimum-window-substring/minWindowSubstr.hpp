/** \file
 * \brief Minimum Window Substring implementation.
 */

#ifndef ALGORITHMS_MIN_WINDOW_SUBSTR_HPP_INCLUDED
#define ALGORITHMS_MIN_WINDOW_SUBSTR_HPP_INCLUDED

#include <iterator>
#include <type_traits>
#include <unordered_map>
#include <utility>

/// Algorithms namespace.
namespace algos {

/// Return type of minWindowSubstr() function.
template <typename Iter>
using ReturnType = std::tuple<Iter, Iter, std::size_t>;

/// Find minimum window substring containing all unique elements of the input range.
/**
 * Complexity:
 * - Time:  O(n)
 * - Space: O(k)
 *
 * where:
 * - n - size of the input range
 * - k - number of unique elements in the input range
 *
 * \tparam ForwardIt iterator type, must meet the requirements of
 *   <a href="https://en.cppreference.com/w/cpp/named_req/ForwardIterator">LegacyForwardIterator</a>
 * \param first begin iterator of the range
 * \param last end (one-past-last) iterator of the range
 *
 * \return
 *   \parblock
 *     `tuple(window_start_iter, window_end_iter, window_length)` representing the minimum substring found
 *
 *      \c window_end_iter is an iterator to one-past-last element of the window
 *   \endparblock
 */
template <typename ForwardIt>
ReturnType<ForwardIt> minWindowSubstr(ForwardIt first, ForwardIt last) {
    static_assert(std::is_base_of_v<std::forward_iterator_tag, typename std::iterator_traits<ForwardIt>::iterator_category>);
    // or is_convertible_v ?

    using value_type = typename std::iterator_traits<ForwardIt>::value_type;
    std::unordered_map<value_type, std::size_t> elementCounts;
    // const iter vs const_iter !
    for (/*const*/auto it = first; it != last; ++it) {
        elementCounts.try_emplace(*it, 0); //vs. insert({*it, 0})
    }
    std::size_t uniqueElems = elementCounts.size(), elemsPresent = 0;

    ForwardIt wStart, wEnd;
    std::size_t wLength;
    bool initialized = false;
    wStart = wEnd = last;
    wLength = 0;

    ForwardIt currStart = first;  // current start inclusive
    ForwardIt newPos = currStart; // current end inclusive
    for(; newPos != last; ++newPos) {
        if (wLength == uniqueElems) { // found the first minimal window
            break;
        }

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
            //if (wLength == uniqueElems) // found the first minimal window

            const auto count = --elementCounts.at(*currStart);
            if (count == 0) {
                --elemsPresent;
            }
            ++currStart;
        }
    }

    return {wStart, wEnd, wLength};
}

//TODO lastMinWindowSubstr()
// easy way: reverse iterator

//TODO minWindowSubstrNoPreproc()
// without first iteration over all elements to put in the map

} // namespace algos

#endif // ALGORITHMS_MIN_WINDOW_SUBSTR_HPP_INCLUDED
