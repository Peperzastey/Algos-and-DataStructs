/** \file
 * \brief Minimum Greater Sequence implementation.
 */

#ifndef ALGORITHMS_MIN_GREATER_NUM_HPP_INCLUDED
#define ALGORITHMS_MIN_GREATER_NUM_HPP_INCLUDED

#include <algorithm>
#include <iterator>
#include <type_traits>
#include <utility> // for std::swap

//TODO remove this docstring from here (?)
/// Algorithms namespace.
namespace algos {

/// Find minimum sequence greater than the given sequence using only the elements of this sequence.
/**
 * Executes in place, modifying the input sequence.
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
 * - n - size of the input sequence
 *
 * \tparam BidirIt
 *   \parblock
 *     iterator type, must meet the requirements of
 *     <a href="https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator">LegacyBidirectionalIterator</a>
 *
 *     \c typename \c std\::iterator_traits<BidirIt>\::value_type must meet the requirements of
 *     <a href="https://en.cppreference.com/w/cpp/named_req/LessThanComparable">LessThanComparable</a>.
 *     This is the only requirement on \c value_type
 *   \endparblock
 * \param first begin iterator of the sequence
 * \param last end (one-past-last) iterator of the sequence
 *
 * \return
 *   - \c true if a minimum greater sequence exists
 *
 *     The input sequence now contains the sequence found
 *   - \c false otherwise
 *
 *     The input sequence is unmodified
 *
 * \see
 *   <a href="https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare">std::lexicographical_compare</a>
 *
 * \todo add ExecutionPolicy - forward it to std::reverse, std::adjacent_find
 */
template <typename BidirIt>
bool minGreaterSeqInPlace(BidirIt first, BidirIt last) {
    // BidirIt must be bidirectional iterator
    //TODO see compiler error without this static_assert
    static_assert(std::is_base_of_v<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>);
    // cannot be const_iterator

    auto revFirst = std::make_reverse_iterator(last);
    auto revLast = std::make_reverse_iterator(first);
    // not using std::greater{} because it uses operator> instead of operator< and we only require LessThanComparable
    // deduced type shall be the same (except cv-qual) as typename std::iterator_traits<BidirIt>::value_type
    //TODO add static_asserts in lambda (just to be 100% sure)
    auto revLastGreater = std::adjacent_find(revFirst, revLast, [](const auto &lhs, const auto &rhs) { return rhs < lhs; });
    if (revLastGreater == revLast) {
        return false;
    }
    auto elemToRight = std::prev(revLastGreater.base()); // &*rit == &*(rit.base() - 1)
    auto firstLess = std::prev(elemToRight);

    //TODO operate on reverse_iterators; std::iter_swap can handle differing iterator types
    //TODO std::find_if
    auto minGreaterElemToRight = elemToRight;
    while (++elemToRight != last) {
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
    // make it non-descending (reverse the right-rest range)

    elemToRight = std::next(firstLess);
    std::reverse(elemToRight, last); // exactly (last - elemToRight)/2 swaps

    return true;
}

} // namespace algos

#endif // ALGORITHMS_MIN_GREATER_NUM_HPP_INCLUDED
