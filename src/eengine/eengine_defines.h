#ifndef EENGINE_DEFINES
#define EENGINE_DEFINES

#include <memory>

template <typename T>
using shared = std::shared_ptr<T>;

template <typename T>
using weak = std::weak_ptr<T>;

template <typename T>
using unique = std::unique_ptr<T>;

#define EENGINE_USING_REND 1

#endif // EENGINE_DEFINES