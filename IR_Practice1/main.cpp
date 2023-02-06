#include <iostream>
#include "ISerializer.h"
#include "TextFileSerializer.h"
#include "Dictionary.h"
using std::cout;

int main()
{
	StdSearchMapDict dict;
	dict.reserve(10000);
	const int num = 100'000'0;
	for (int i = 0; i < num; ++i)
	{
		dict.add_word("word" + std::to_string(i));
	}

	ISerializer<StdSearchMapDict>* ser = new TextFileSerializer();
	ser->serialize("myFile.txt", dict);
	auto dasa = ser->deserialize("myFile.txt");
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