//#ifndef BIN_SEARCH_POLICY_
//#define BIN_SEARCH_POLICY_
//
//template<typename WordType>
//struct BinarySearchPolicy
//{
//public:
//	using word_type = WordType;
//public:
//
//	template<typename Container, typename Word>
//	static void add_word(Container& container, Word&& word)
//	{
//		auto index = find_word(container, word);
//		if (index < container.size())
//		{
//			auto& [word_, count_] = container[index];
//			if (word_ == word)
//			{
//				++count_;
//			}
//			else
//			{
//				const auto to_insert = container.begin() + index;
//				container.insert(to_insert, { std::forward<Word>(word), 1u });
//			}
//		}
//		else
//		{
//			const auto to_insert = container.begin() + index;
//			container.insert(to_insert, { std::forward<Word>(word), 1u });
//		}
//		//auto elm = find_word(container, word);
//		//auto end = container.end();
//		//if (elm == end)
//		//{
//		//	container.push_back({ std::forward<Word>(word), 1u });
//		//	//container.insert({ std::forward<Word>(word), 1u });
//		//	return;
//		//}
//
//		//auto& [word_, count_] = *elm;
//		//if(word_ == word)
//		//{
//		//	++count_;
//		//}
//		//else
//		//{
//		//	container.insert(elm, { std::forward<Word>(word), 1u });
//		//}
//
//
//
//		/*auto elm = find_word(container, word);
//		auto end = container.end();
//
//		if (elm == end)
//		{
//			container.insert(elm, { std::forward<Word>(word), 1u });
//			return;
//		}
//
//		auto& [found_word, found_count] = *elm;
//
//		if(found_word == word)
//		{
//			++found_count;
//		}
//		else
//		{
//			container.insert(elm, { std::forward<Word>(word), 1u });
//		}*/
//	}
//
//	template<typename Container>
//	static bool has_word(const Container& container, const word_type& word) noexcept
//	{
//		/*auto elm = find_word(container, word);
//		auto end = container.end();
//		if (elm == end) return false;
//		const auto& [found_word, _] = *elm;
//		return found_word == word;*/
//		return true;
//	}
//
//	template<typename Container>
//	static typename Container::size_type find_word
//	(
//		Container& container, 
//		const word_type& word
//	) noexcept
//	{
//		//static_assert(!std::is_const_v<Container>, "FUCK CONST WHY???");
//		typename Container::size_type left = 0;
//		typename Container::size_type right = container.size() - 1;
//
//		if (container.empty()) return left;
//		while (left <= right)
//		{
//			auto next = left + (right - left) / 2;
//			const auto& [word_, _] = container[next];
//			if (word_ == word) return next;
//			if (word_ < word)	left = next + 1;
//			else				right = next - 1;
//		}
//
//		return left;
//	}
//
//	template<typename Container>
//	static typename Container::size_type find_word
//	(
//		const Container& container, 
//		const word_type& word
//	) noexcept
//	{
//		typename Container::size_type left = 0;
//		typename Container::size_type right = container.size() - 1;
//
//		while (left <= right)
//		{
//			auto next = left + (right - left) / 2;
//			const auto& [word_, _] = container[next];
//			if (word_ == word) return next;
//			if (word_ < word)	left = next + 1;
//			else				right = next - 1;
//		}
//
//		return left;
//		/*auto left = container.begin();
//		auto right = container.end();
//
//		while (left <= right)
//		{
//			auto next = left + (right - left) / 2;
//			const auto& [found_word, _] = *next;
//			if (found_word == word) return next;
//			if (found_word < word)	left = next + 1;
//			else					right = next - 1;
//		}
//
//		return left;*/
//	}
//};
//
//#endif // !BIN_SEARCH_POLICY_
