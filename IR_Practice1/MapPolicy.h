#ifndef MAP_POLICY_
#define MAP_POLICY_

template<typename WordType>
struct MapPolicy
{
public:
	using word_type = WordType;

public:

	template<typename Container, typename Word>
	static void add_word(Container& container, Word&& word)
	{
		if (!has_word(container, word))
		{
			container.insert({ std::forward<Word>(word), 1u });
		}
		else
		{/*
			auto& [_, found_count] = *elm;
			++found_count;*/
			++container[word];
		}
	}

	template<typename Container>
	static bool has_word(const Container& container, const word_type& word) noexcept
	{
		return container.contains(word);//find_word(container, word) != container.end();
	}
};

#endif // !MAP_POLICY_
