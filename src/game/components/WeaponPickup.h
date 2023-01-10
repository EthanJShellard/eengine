#include <eengine/eengine.h>

class WeaponPickup : public eengine::Component 
{
	float m_bobDistance;
	float m_startingHeight;
	float m_bobSpeed, m_bobProgress;
	float m_rotationSpeed;
	shared<eengine::Transform> m_transform;

	void OnBegin() override;
	void OnTick(float _deltaTime) override;
	void OnTriggerEnter(shared<eengine::RigidBody> _other) override;

public:
	WeaponPickup(float _bobDistance, float _bobSpeed, float _rotationSpeed);
};