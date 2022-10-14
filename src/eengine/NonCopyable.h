#ifndef EENGINE_NONCOPYABLE
#define EENGINE_NONCOPYABLE
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