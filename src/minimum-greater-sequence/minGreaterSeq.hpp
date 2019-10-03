/** \file
 * \brief Minimum Greater Sequence implementation.
 */

#ifndef ALGORITHMS_MIN_GREATER_NUM_HPP_INCLUDED
#define ALGORITHMS_MIN_GREATER_NUM_HPP_INCLUDED

#include <algorithm>
#include <cassert>
#include <iterator>
#include <type_traits>
#include <utility> // std::declval

//TODO remove this docstring from here? (duplicate)
/// Algorithms namespace.
namespace algos {

namespace {

// primary template handles types that do not support operator<
template <typename, typename = std::void_t<> >
struct has_operator_less : std::false_type {};

// specialization recognizes types that do support operator<
template <typename T>
struct has_operator_less<T,
        std::void_t<decltype( std::declval<T>() < std::declval<T>() )>
    > : std::true_type {};

template <typename T>
inline constexpr bool has_operator_less_v = has_operator_less<T>::value;

} // anonymous namespace

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
 *     and
 *     <a href="https://en.cppreference.com/w/cpp/named_req/ValueSwappable">ValueSwappable</a>
 *
 *     \c typename \c std\::iterator_traits<BidirIt>\::value_type must meet the requirements of
 *     <a href="https://en.cppreference.com/w/cpp/named_req/LessThanComparable">LessThanComparable</a>.
 *     (and
 *     <a href="https://en.cppreference.com/w/cpp/named_req/Swappable">Swappable</a>)
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
 * \todo add second version of this algorithm: minGreaterSeqInPlace(BidirIt first, BidirIt last, Compare comp)
 *   where Compare is a <a href="https://en.cppreference.com/w/cpp/named_req/BinaryPredicate">BinaryPredicate</a>
 */
template <typename BidirIt>
bool minGreaterSeqInPlace(BidirIt first, BidirIt last) {
    using value_type = typename std::iterator_traits<BidirIt>::value_type;
    static_assert(std::is_base_of_v<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>);
    static_assert(has_operator_less_v<value_type>);
    static_assert(std::is_convertible_v<decltype( std::declval<value_type>() < std::declval<value_type>() ), bool>);
    static_assert(std::is_swappable_v<value_type>);
    // cannot be const_iterator

    auto revFirst = std::make_reverse_iterator(last);
    auto revLast = std::make_reverse_iterator(first);
    // not using std::greater{} because it uses operator> instead of operator< and we only require LessThanComparable
    // deduced type shall be the same (except cv-qual) as typename std::iterator_traits<BidirIt>::value_type
    //TODO add static_asserts in lambda (just to be 100% sure)
    auto revLastGreater = std::adjacent_find(revFirst, revLast, [](const auto &lhs, const auto &rhs) { // O(distance) comparisons
        // use std::decay_t<T> as short for std::remove_cv_t<std::remove_reference_t<T> >
        //TODO check if it makes any problems
        static_assert(std::is_same_v<value_type, std::decay_t<decltype(lhs)> >);
        static_assert(std::is_same_v<value_type, std::decay_t<decltype(lhs)> >);
        return rhs < lhs;
    });
    if (revLastGreater == revLast) {
        return false;
    }
    auto revFirstLess = std::next(revLastGreater);

    // the right-rest is always in non-descending order (looking from right to left)
    auto revMinGreaterElemToRight = std::upper_bound(revFirst, revFirstLess, *revFirstLess); // O(lg(distance)) comparisons
    assert(revMinGreaterElemToRight != revFirstLess);

    std::iter_swap(revFirstLess, revMinGreaterElemToRight); // uses ADL to find swap() for value_type

    // make the order of right-rest non-ascending (reverse it)
    std::reverse(revFirst, revFirstLess); // exactly distance/2 swaps

    return true;
}

} // namespace algos

#endif // ALGORITHMS_MIN_GREATER_NUM_HPP_INCLUDED
