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
	glm::vec3 m_rocketScale;
	float m_rocketSpeed;
	glm::vec3 m_rocketColliderScale;
	float m_viewAngleLimit;
	bool m_hasWeapon;

	shared<eengine::RigidBody> m_rigidBody;
	shared<eengine::Transform> m_transform;
	shared<eengine::AudioSource> m_audioSource;
	shared<eengine::ModelRenderer> m_weaponRenderer;
	shared<eengine::Transform> m_weaponTransform;
	shared<eengine::Transform> m_rocketTransform;
	shared<eengine::RigidBody> m_rocketRigidBody;
	shared<eengine::AudioSource> m_rocketAudioSource;
	shared<eengine::Sound> m_rocketBoostSound;
};