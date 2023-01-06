#include <eengine/eengine.h>

namespace eengine 
{
	class RigidBody;
	class Input;
}

class PlayerController : public eengine::Component 
{
public:
	void OnBegin() override;

private:
	void OnTick(float _deltaTime) override;
	void OnLateTick(float _deltaTime) override;

	float m_playerSpeed;
	glm::vec3 m_camOffset;
	float m_viewAngleLimit;
	shared<eengine::RigidBody> m_rigidBody;
	shared<eengine::Transform> m_transform;
};