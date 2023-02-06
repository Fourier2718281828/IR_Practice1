#include <iostream>
#include <chrono>
#include <filesystem>
#include "ISerializer.h"
#include "LineReader.h"
#include "TextFileSerializer.h"
#include "Dictionary.h"
using std::cout;

std::ifstream::pos_type filesize(const std::string& filename)
{
	std::ifstream in(filename);
	return in.tellg();
}

template<typename Dictionary>
bool check_for_equality(const Dictionary& dict1, const Dictionary& dict2)
{
	for (auto&& [a, b] : dict1)
	{
		if (!dict2.has_word(a))
		{
			return false;
		}
	}

	for (auto&& [a, b] : dict2)
	{
		if (!dict1.has_word(a))
		{
			return false;
		}
	}
}

template<typename Dictionary>
void test(const std::string& dirpath, const std::string& outpath)
{
	cout << "<------------------------------------------>\n";
	cout << "Testing " << typeid(Dictionary::policy_type).name() << '\n';
	cout << ">------------------------------------------<\n";
	Dictionary dict;
	IReader<decltype(dict)>* reader = new LineReader<Dictionary>(" ,.;:!?*[]()\"\"0123456789/\\-");
	try
	{
		size_t total_words = 0u;
		auto file_collection_size = 2342u;
		for (const auto& path : std::filesystem::directory_iterator(dirpath))
		{
			cout << "# \"" << path.path().string() << "\" processing...\n";
			auto start = std::chrono::steady_clock::now();
			total_words += reader->read(path.path().string(), dict);
			auto end = std::chrono::steady_clock::now();
			auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
			cout << "\tread in " << time1 << " ms\n";
		}

		cout << ">------------------------------------------<\n";

		ISerializer<StdSearchMapDict>* ser = new TextFileSerializer();

		cout << "# Serialization processing...\n";
		auto start = std::chrono::steady_clock::now();
		ser->serialize(outpath, dict);
		auto end = std::chrono::steady_clock::now();
		auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		cout << "\tdone in " << time1 << " ms\n";


		cout << ">------------------------------------------<\n";
		cout << "# Decerialization processing...\n";
		auto start2 = std::chrono::steady_clock::now();
		auto data = ser->deserialize(outpath);
		auto end2 = std::chrono::steady_clock::now();
		auto time12 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();
		cout << "\tdone in " << time12 << " ms\n";

		cout << ">------------------------------------------<\n";
		{
			cout << "# Checking for equality of deceralized and original dict...\n";
			auto start2 = std::chrono::steady_clock::now();
			bool check = check_for_equality<Dictionary>(dict, data);
			auto end2 = std::chrono::steady_clock::now();
			auto time12 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();
			cout << "\tdone in " << time12 << " ms\n";
			cout << "RESULT : " << std::boolalpha << check << '\n';
		}
		cout << ">------------------------------------------<\n";

		cout << "STATISTICS:\n";
		cout << "\tGeneral file collection size \t= " << file_collection_size << '\n';
		cout << "\tGeneral number of words \t= " << total_words << '\n';
		cout << "\tTotal size of produced dict \t= " << dict.size() << '\n';

		cout << "<------------------------------------------>\n";

		delete reader; reader = nullptr;
		delete ser; ser = nullptr;
	}
	catch (std::exception& ex)
	{
		cout << "ERROR : " << ex.what() << '\n';
	}
}


int main()
{
	const std::string path = "Input Files/";
	const std::string output = "Output Files/output.txt";
	test<StdSearchMapDict>(path, output);
	test<StdSearchArrayDict>(path, output);
	StdSearchArrayDict d1, d2;
	check_for_equality(d1, d2);

	return EXIT_SUCCESS;
}