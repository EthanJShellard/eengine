#include "eengine/eengine.h"


class Explosion : public eengine::Component 
{
	float m_range;
	float m_force;
	float m_timer;
	float m_timeToDecay;

	shared<eengine::ModelRenderer> m_renderer;

	void OnBegin() override;
	void OnTick(float _deltaTime) override;
	void OnLateTick(float _deltaTime) override;
	void OnTriggerEnter(shared<eengine::RigidBody> _other) override;
public:
	Explosion(float _range, float _force, float _decayTime);
};