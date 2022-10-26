#ifndef EENGINE_NONCOPYABLE
#define EENGINE_NONCOPYABLE

/// @brief A super-class which can be inherited from to prevent copying.
class NonCopyable
{
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable&);
	NonCopyable& operator=(const NonCopyable&);
};
#endif // !EENGINE_NONCOPYABLE