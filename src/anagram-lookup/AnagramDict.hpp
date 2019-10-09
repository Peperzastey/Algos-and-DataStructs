/** \file
 * \brief AnagramDict implementation.
 */

#ifndef ALGORITHMS_ANAGRAM_DICT_HPP_INCLUDED
#define ALGORITHMS_ANAGRAM_DICT_HPP_INCLUDED

#include <algorithm> // std::max
#include <cassert>
#include <cctype> // std::toupper
//#include <functional> // std::hash, std::equal_to
//#include <memory> // std::allocator
#include <stdexcept>
#include <unordered_map> //TODO pimpl ?
//#include <utility> // std::pair

namespace algos {

//template <typename T> //mapped_type
class AnagramStringKeyCalculator {
public:
    using key_type = std::string;
    using mapped_type = std::string;

public:
    //CAUTION works up to max 9 occurrences of the same letter in value!
    key_type calculateKey(const mapped_type &value) const {
        key_type key{};
        auto maxPos = -1;
        for (auto letter : value) {
            letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
            auto pos = letterPos_.at(letter);
            if (key.size() <= pos) {
                key.append(pos - key.size() + 1, '0');
            }
            auto &valueNum = key[pos];
            if (valueNum == '9') {
                throw std::invalid_argument{"There can be max 9 occurrences of the same letter in value"};
            }
            valueNum += 1; // ASCII encoding
            maxPos = std::max(maxPos, static_cast<int>(pos));
        }
        assert(key.size() == static_cast<std::size_t>(maxPos) + 1);
        return key; // NRVO (copy elision)
    }

private:
    // based on English alphabet letter frequency
    // from most to least frequent:
    //TODO move initialization to function called by ctor; bucket_count = init_list.size()
    //TODO proper hash function! : ascii_code(key) - ascii_code('A') % 26
    const std::unordered_map<char, unsigned char> letterPos_ {
        {
            {'E', 0}, {'T', 1}, {'A', 2}, {'O', 3}, {'I', 4}, {'N', 5},
            {'S', 6}, {'R', 7}, {'H', 8}, {'D', 9}, {'L', 10}, {'U', 11},
            {'C', 12}, {'M', 13}, {'F', 14}, {'Y', 15}, {'W', 16}, {'G', 17},
            {'P', 18}, {'B', 19}, {'V', 20}, {'K', 21}, {'X', 22}, {'Q', 23},
            {'J', 24}, {'Z', 25}
        },
        26 // (minimal) bucket count
    };
};

//template <typename T, typename Container> // Container<T>
template <
    typename KeyCalculator = AnagramStringKeyCalculator,
    typename Hash = std::hash<std::string>,
    typename KeyEqual = std::equal_to<std::string>,
    typename Allocator = std::allocator< std::pair<const std::string, std::string> >
> class BasicAnagramDict;

//using AnagramDict = BasicAnagramDict<std::string>;
using AnagramDict = BasicAnagramDict<>;

// typename SequenceType
//TODO remove default values from here? - are already present in forward declaration
template <
    typename KeyCalculator,
    typename Hash,
    typename KeyEqual,
    typename Allocator
> class BasicAnagramDict {
private:
    using underlying_container = std::unordered_multimap<std::string, std::string,
        Hash, KeyEqual, Allocator>;

public:
    using key_type = std::string;
    using mapped_type = std::string;
    using value_type = std::pair<const key_type, mapped_type>;
    using iterator = typename underlying_container::iterator;
    using const_iterator = typename underlying_container::const_iterator;
    // local_iterator ?

public:
    //TODO can I move definitions to .cpp file?
    std::pair<const_iterator, const_iterator> findAnagrams(const mapped_type &value) const {
        auto key = keyCalculator_.calculateKey(value);
        return multimap_.equal_range(key);
    }

    // cannot emplace() because we need to construct mapped_type for key calculation!

    //TODO std::pair<iterator,bool>
    iterator insert(const mapped_type &value) {
        //TODO if this string already exists - do not add (like in set)
        auto key = keyCalculator_.calculateKey(value);
        return multimap_.insert({std::move(key), value});
    }

    //TODO std::pair<iterator,bool>
    iterator insert(mapped_type &&value) {
        auto key = keyCalculator_.calculateKey(value);
        return multimap_.insert({std::move(key), std::move(value)});
    }

private:
    KeyCalculator keyCalculator_;
    underlying_container multimap_;
};

} // namespace algos

#endif // ALGORITHMS_ANAGRAM_DICT_HPP_INCLUDED
