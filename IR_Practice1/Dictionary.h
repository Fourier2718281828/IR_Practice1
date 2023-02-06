#ifndef DICTIONARY_
#define DICTIONARY_
#include <type_traits>
#include <unordered_map>
#include <vector>
#include "DefaultAddPolicy.h"

template
<
	typename WordType,
	typename IndexType,
	template<class, class> typename Container,
	template<class> typename AddElementPolicy = StdSearchPolicy
>
class Dictionary
{
public:
	using word_type = WordType;
	using index_type = IndexType;
private:
	using container_type = Container<word_type, index_type>;
public:
	using value_type = typename container_type::value_type;
private:
	using policy_type = AddElementPolicy<word_type>;
public:
	static_assert(std::is_same_v<typename policy_type::word_type, word_type>,
		"Policy value_type and dictionary value_type must coincide.");
	static_assert(std::is_arithmetic_v<index_type>, "Index type must be arithmetic.");

public:

	constexpr Dictionary() noexcept : container_{} {}

	Dictionary(const Dictionary&) = delete;

	Dictionary& operator=(const Dictionary&) = delete;

	Dictionary(Dictionary&&) = default;

	Dictionary& operator=(Dictionary&&) = default;

public:

	void add_word(const word_type& word)
	{
		policy_type::add_word(container_, word);
	}

	void add_word(word_type&& word)
	{
		policy_type::add_word(container_, std::move(word));
	}

	[[nodiscard]] bool has_word(const word_type& word) const noexcept
	{
		return policy_type::has_word(container_, word);
	}

	[[nodiscard]] constexpr container_type::iterator begin() noexcept
	{
		return container_.begin();
	}

	[[nodiscard]] constexpr container_type::iterator end() noexcept
	{
		return container_.end();
	}

	[[nodiscard]] constexpr container_type::const_iterator begin() const noexcept
	{
		return container_.begin();
	}

	[[nodiscard]] constexpr container_type::const_iterator end() const noexcept
	{
		return container_.end();
	}

	[[nodiscard]] constexpr container_type::const_iterator cbegin() noexcept
	{
		return container_.cbegin();
	}

	[[nodiscard]] constexpr container_type::const_iterator cend() noexcept
	{
		return container_.cend();
	}

	void reserve(const typename container_type::size_type size)
	{
		container_.reserve(size);
	}

private:
	container_type container_;
};



template<typename U, typename W>
using map = std::unordered_map<U, W>;

template<typename U, typename W>
using vec = std::vector<std::pair<U, W>>;

using StdSearchMapDict = Dictionary
<
	std::string, 
	std::size_t, 
	map, 
	StdSearchPolicy
>;

using StdSearchArrayDict = Dictionary
<
	std::string,
	std::size_t,
	vec,
	StdSearchPolicy
>;

//using BinSearchArrayDict = Dictionary
//<
//	std::string,
//	std::size_t,
//	vec,
//	BinarySearchPolicy
//>;

#endif // !DICTIONARY_
