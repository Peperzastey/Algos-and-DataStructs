/** \file
 * \brief Minimum Greater Sequence implementation.
 */

#ifndef ALGORITHMS_MIN_GREATER_NUM_HPP_INCLUDED
#define ALGORITHMS_MIN_GREATER_NUM_HPP_INCLUDED

#include <utility> // for std::swap
#include <algorithm>
#include <iterator>

//TODO remove this docstring from here (?)
/// Algorithms namespace.
namespace algos {

/// Find minimum sequence greater than the given sequence using only the elements of this sequence.
/**
 * Executes in-place, modifying the input range.
 *
 * Complexity:
 * - Time:  O(n)
 * - Space: O(1)
 *
 * where:
 * - n - size of the input range
 *
 * \tparam Iter iterator type, must meet the requirements of
 * <a href="https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator">LegacyBidirectionalIterator</a>
 * \param first begin iterator of the range
 * \param last end (one-past-last) iterator of the range
 *
 * \return
 * -  \c true if the sequence has been found
 *
 *    The input range now contains the sequence found
 * -  \c false otherwise
 */
template <typename Iter>
bool minGreaterSeqInPlace(Iter first, Iter last) {
    // Iter must be bidirectional iterator
    // cannot be const_iterator
    //TODO add static_asserts
    if (first == last) { // empty range
        return false;
    }
    if (std::distance(first, last) == 1) { // only one elem
        return false;
    }

    auto elemToRight = std::prev(last);
    auto firstLesser = std::prev(elemToRight);
    while (!(*firstLesser < *elemToRight)) {
        if (firstLesser == first) {
            return false;
        }
        elemToRight = firstLesser;
        firstLesser = std::prev(firstLesser); //TODO std::advance
    }

    auto minGreaterElemToRight = elemToRight;
    while ((elemToRight = std::next(elemToRight)) != last) {
        if ((*firstLesser < *elemToRight) && (*elemToRight < *minGreaterElemToRight)) { // != in the second check is enough
            minGreaterElemToRight = elemToRight;
        }
    }

    //using std::swap; // use ADL // std::iter_swap already uses it
    std::iter_swap(firstLesser, minGreaterElemToRight);

    // the right-rest always in non-ascending order (from left to right)
    // sometimes already in non-descending order (e.g. 1222 -> 2122)
    // make it non-descending

    elemToRight = std::next(firstLesser);
    if (minGreaterElemToRight == elemToRight) { // the right-rest is already in non-descending order
        return true;
    }
    last = std::prev(last); //TODO std::advance
    //TODO if constexpr (random access iterator) --> use operator< on iterators
    // operator< on iterators needs a LegacyRandomAccessIterator
    while (elemToRight != last && std::prev(elemToRight) != last) {
        std::iter_swap(elemToRight, last);
        elemToRight = std::next(elemToRight); //TODO std::advance
        last = std::prev(last); //TODO std::advance
    }

    return true;
}

//TODO must work for reverse iterators
//TODO types with working std::next(it) but not ++it

} // namespace algos

#endif // ALGORITHMS_MIN_GREATER_NUM_HPP_INCLUDED
