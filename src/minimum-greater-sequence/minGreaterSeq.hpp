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
 * Executes in place, modifying the input range.
 *
 * The sequences are compared lexicographically.
 * This means that sequence A is a minimum sequence greater than sequence B (both of which contain only
 * the elements present in sequence B) iff A is lexicographically greater than B and lexicographically less
 * than all other sequences that are lexicographically greater than B (containing only the elements present in B).
 *
 * Complexity:
 * - Time:  O(n)
 * - Space: O(1)
 *
 * where:
 * - n - size of the input range
 *
 * \tparam Iter iterator type, must meet the requirements of
 *   <a href="https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator">LegacyBidirectionalIterator</a>
 * \param first begin iterator of the range
 * \param last end (one-past-last) iterator of the range
 *
 * \return
 *   - \c true if the sequence has been found
 *
 *     The input range now contains the sequence found
 *   - \c false otherwise
 *
 * \see
 *   <a href="https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare">std::lexicographical_compare</a>
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
    auto firstLess = std::prev(elemToRight);
    while (!(*firstLess < *elemToRight)) {
        if (firstLess == first) {
            return false;
        }
        elemToRight = firstLess;
        firstLess = std::prev(firstLess); //TODO std::advance
    }

    auto minGreaterElemToRight = elemToRight;
    while ((elemToRight = std::next(elemToRight)) != last) {
        if ((*firstLess < *elemToRight) && !(*minGreaterElemToRight < *elemToRight)) {
            // swap with the last min-greater elem
            // this breaks stability (meaning as in sort) -- TODO try to repair
            minGreaterElemToRight = elemToRight;
            //TODO try checking if all elems are equal
        }
    }

    //using std::swap; // use ADL // std::iter_swap already uses it
    std::iter_swap(firstLess, minGreaterElemToRight);

    // the right-rest is always in non-ascending order (from left to right)
    // sometimes already in non-descending order (e.g. 1222 -> 2122)
    // make it non-descending

    elemToRight = std::next(firstLess);
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
