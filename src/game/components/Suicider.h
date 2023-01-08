#include <eengine/eengine.h>

class Suicider : public eengine::Component
{
public:
	Suicider();
	Suicider(int _target);

private:
	void OnTick(float _deltaTime) override;
	void OnTriggerEnter(shared<eengine::RigidBody> _other) override;
	void OnTriggerExit(shared<eengine::RigidBody> _other) override;

	int m_count;
	int m_target;
};