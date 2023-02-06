#include <iostream>
#include "ISerializer.h"
#include "LineReader.h"
#include "TextFileSerializer.h"
#include "Dictionary.h"
using std::cout;

int main()
{
	StdSearchMapDict dict;
	const std::string filename = "Input Files/1.txt";
	IReader<decltype(dict)>* reader = new LineReader(" ,.;:!?*[]()\"\"0123456789/\\-");
	reader->read(filename, dict);
	ISerializer<StdSearchMapDict>* ser = new TextFileSerializer();
	ser->serialize(filename, dict);
	auto dasa = ser->deserialize(filename);
	delete ser;

	for (auto&& [a, b] : dict)
	{
		if (!dasa.has_word(a))
		{
			cout << a << '\n';
		}
	}
	cout << "------------" << '\n';

	for (auto&& [a, b] : dasa)
	{
		if (!dict.has_word(a))
		{
			cout << a << '\n';
		}
	}

	return EXIT_SUCCESS;
}