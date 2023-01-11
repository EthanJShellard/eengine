#include "eengine/eengine.h"


class RocketController : public eengine::Component 
{
	float m_timer;
	float m_maxTime;
	float m_explosionRange;
	float m_explosionForce;
	float m_explosionDamage;
	shared<eengine::Sound> m_explosionSound;

	void Explode();

	void OnBegin() override;
	void OnTick(float _deltaTime) override;
	void OnTriggerEnter(shared<eengine::RigidBody> _other) override;

public:
	RocketController(float _timeLimit);
};