#ifndef APPEND_POLICY_
#define APPEND_POLICY_

template<typename WordType>
struct StdSearchPolicy
{
public:
	using word_type = WordType;

public:

	template<typename Container, typename Word>
	static void add_word(Container& container, Word&& word)
	{
		auto elm = find_word(container, word);
		auto end = container.end();
		if (elm == end)
		{
			container.push_back({ std::forward<Word>(word), 1u });
			//container.insert({ std::forward<Word>(word), 1u });
		}
		else
		{
			auto& [_, found_count] = *elm;
			++found_count;
		}
	}

	template<typename Container>
	static bool has_word(const Container& container, const word_type& word) noexcept
	{
		return find_word(container, word) != container.end();
	}

	template<typename Container>
	static typename Container::iterator find_word
	(Container& container, const word_type& word) noexcept
	{
		return std::find_if
		(
			container.begin(),
			container.end(),
			[&word](const auto& pair) { return pair.first == word; }
		);
	}

	template<typename Container>
	static typename Container::const_iterator find_word
	(const Container& container, const word_type& word) noexcept
	{
		return std::find_if
		(
			container.begin(),
			container.end(),
			[&word](const auto& pair) { return pair.first == word; }
		);
	}
};

#endif // !APPEND_POLICY_
