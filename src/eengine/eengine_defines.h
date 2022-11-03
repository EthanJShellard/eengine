#ifndef EENGINE_DEFINES
#define EENGINE_DEFINES

#include <memory>

template <typename T>
using shared = std::shared_ptr<T>;

template <typename T>
using weak = std::weak_ptr<T>;

template <typename T>
using unique = std::unique_ptr<T>;

#define COMPONENT(T)\
class T##WRAPPER : public eengine::Component\
{\
	public:\
	const char * GetName() const\
	{\
		return #T;\
	}\
};\
class T : public T##WRAPPER\

#endif // EENGINE_DEFINES