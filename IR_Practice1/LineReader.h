#ifndef LINE_READER_
#define LINE_READER_
#include "IReader.h"
#include "Dictionary.h"
#include "Utilities.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <fstream>


bool invalidChar(char c) noexcept
{
	return !(c >= 0 && c < 128);
}

void stripUnicode(std::string& str)
{
	str.erase(std::remove_if(str.begin(), str.end(), &invalidChar), str.end());
}

template<typename Dictionary>
class LineReader : public IReader<Dictionary>
{
public:
	using dict_type = Dictionary;

public:

	constexpr LineReader(const std::string& delims) noexcept : 
		delims_(delims) {}

public:

	size_t read(const std::string& filename, dict_type& res) const override
	{
		std::string line;
		std::ifstream file(filename);
		size_t words_total_count = 0u;
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				::stripUnicode(line);
				to_lower_case(line);
				auto words = tokenize(line, delims_);
				for (auto&& word : words)
				{
					if (!word.empty())
					{
						res.add_word(word); 
						++words_total_count;
					}
				}
			}
			return words_total_count;
		}
		else
		{
			file.close();
			throw std::runtime_error("Could not open the file: " + filename);
		}
		file.close();
	}

private:

	void to_lower_case(std::string& data) const noexcept
	{
		std::transform
		(
			data.begin(), 
			data.end(), 
			data.begin(),
			[](unsigned char c) { return std::tolower(c); }
		);
	}

private:
	const std::string delims_;
};



#endif // !LINE_READER_
