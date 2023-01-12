#include <eengine/eengine.h>


class DoorCrate : public eengine::Component 
{
	void OnCollisionEnter(shared<eengine::RigidBody> _other) override;
};