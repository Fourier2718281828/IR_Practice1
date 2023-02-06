#pragma once
#include <fstream>
#include "ISerializer.h"
#include "Dictionary.h"

//template<typename Dictionary>
using Dict = StdSearchMapDict;
class TextFileSerializerMap : public ISerializer<Dict>
{
public:
	void serialize(const std::string& filename, const Dict& dict) const override
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

	Dict deserialize(const std::string& filename) const override
	{
		std::ifstream fin(filename);
		if (fin.is_open())
		{
			Dict::container_type res{};
			decltype(res)::size_type size;
			Dict::index_type read_count;
			Dict::word_type read_word;

			fin >> size;

			for (decltype(size) i = 0u; i < size; ++i)
			{
				fin >> read_count >> read_word;
				res.insert({ read_word, read_count });
			}

			return Dict{ std::move(res) };
		}
		else
		{
			fin.close();
			throw std::runtime_error("Could not open the file: " + filename);
		}

		fin.close();
	}
};

class TextFileSerializerArray : public ISerializer<StdSearchArrayDict>
{
public:
	void serialize(const std::string& filename, const StdSearchArrayDict& dict) const override
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

	StdSearchArrayDict deserialize(const std::string& filename) const override
	{
		std::ifstream fin(filename);
		if (fin.is_open())
		{
			StdSearchArrayDict::container_type res{};
			decltype(res)::size_type size;
			StdSearchArrayDict::index_type read_count;
			StdSearchArrayDict::word_type read_word;

			fin >> size;

			for (decltype(size) i = 0u; i < size; ++i)
			{
				fin >> read_count >> read_word;
				res.push_back({ read_word, read_count });
			}

			return StdSearchArrayDict{ std::move(res) };
		}
		else
		{
			fin.close();
			throw std::runtime_error("Could not open the file: " + filename);
		}

		fin.close();
	}
};
