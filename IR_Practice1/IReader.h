#ifndef IREADER_
#define IREADER_
#include <string>

template<typename Dictionary>
class IReader
{
public:
	virtual void read(const std::string&, Dictionary&) const = 0;
};

#endif // !IREADER_
