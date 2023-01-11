#include "eengine/eengine.h"


class RocketController : public eengine::Component 
{
	float m_timer;
	float m_maxTime;

	void Explode();

	void OnTick(float _deltaTime) override;
	void OnTriggerEnter(shared<eengine::RigidBody> _other) override;

public:
	RocketController(float _timeLimit);
};