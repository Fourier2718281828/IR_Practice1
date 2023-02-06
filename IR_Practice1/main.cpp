#include <iostream>
#include "Dictionary.h"
using std::cout;


int main()
{
	/*Dictionary<std::string, size_t, map> aa;
	map<int, int> vvvv;
	aa.add_word("fuck my ass");
	aa.add_word("fuck my ass");
	std::string a = "asda";
	aa.add_word(a);
	cout << (aa.has_word("asda")) << '\n';
	cout << (aa.has_word("asda12")) << '\n';*/

	StdSearchArrayDict dict;
	dict.add_word("Fucky2");
	dict.add_word("Fucky2");
	dict.add_word("Fucky3");
	dict.add_word("Fucky3");
	dict.add_word("Fucky1");
	dict.add_word("Fucky1");
	dict.add_word("Fucky2");
	dict.add_word("Fucky3");
	dict.add_word("Fucky3");
	cout << dict.has_word("Fucky1") << '\n';
	cout << dict.has_word("Fucky2") << '\n';
	cout << dict.has_word("Fucky3") << '\n';
	cout << dict.has_word("Fucky4") << '\n';

	return EXIT_SUCCESS;
}