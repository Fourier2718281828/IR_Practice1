#ifndef I_SERIALIZER_
#define I_SERIALIZER_
#include <string>

template<typename Dictionary>
class ISerializer
{
public:
	virtual ~ISerializer() = default;
public:
	virtual void serialize(const std::string&, const Dictionary&) const = 0;
	virtual Dictionary deserialize(const std::string&) const = 0;
};

#endif // !I_SERIALIZER_
