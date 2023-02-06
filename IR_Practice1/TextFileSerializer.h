#pragma once
#include <fstream>
#include "ISerializer.h"
#include "Dictionary.h"

//template<typename Dictionary>
class TextFileSerializer : public ISerializer<StdSearchMapDict>
{
public:
	void serialize(const std::string& filename, const StdSearchMapDict& dict) const override
	{
		std::ofstream fout(filename);
		if (fout.is_open())
		{
			fout << dict.size() << '\n';
			for (auto&& [word, count] : dict)
			{
				fout << count << ' ' << word << '\n';
			}
		}
		else
		{
			fout.close();
			throw std::runtime_error("Could not open the file: " + filename);
		}

		fout.close();
	}

	StdSearchMapDict deserialize(const std::string& filename) const override
	{
		std::ifstream fin(filename);
		if (fin.is_open())
		{
			StdSearchMapDict::container_type res{};
			decltype(res)::size_type size;
			StdSearchMapDict::index_type read_count;
			StdSearchMapDict::word_type read_word;

			fin >> size;

			for (decltype(size) i = 0u; i < size; ++i)
			{
				fin >> read_count >> read_word;
				res.insert({ read_word, read_count });
			}

			return StdSearchMapDict{ std::move(res) };
		}
		else
		{
			fin.close();
			throw std::runtime_error("Could not open the file: " + filename);
		}

		fin.close();
	}
};
