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

	void GiveWeapon();

private:
	void OnTick(float _deltaTime) override;
	void OnLateTick(float _deltaTime) override;

	float m_playerSpeed;
	float m_aerialSpeed;
	glm::vec3 m_camOffset;
	glm::vec3 m_weaponOffset;
	glm::vec3 m_weaponScale;
	float m_viewAngleLimit;
	bool m_hasWeapon;

	shared<eengine::RigidBody> m_rigidBody;
	shared<eengine::Transform> m_transform;
	shared<eengine::ModelRenderer> m_weaponRenderer;
	shared<eengine::Transform> m_weaponTransform;
};