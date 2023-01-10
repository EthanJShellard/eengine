#include "Component.h"
#include "RenderContext.h"

namespace eengine
{
	shared<Entity> Component::GetParent()
	{
		return m_parent.lock();
	}

	shared<Core> Component::GetCore() 
	{
		return m_core.lock();
	}

	shared<Input> Component::GetInput() 
	{
		return m_input.lock();
	}

	void Component::OnInit() 
	{
		// Stub
	}

	void Component::OnBegin() 
	{
		// Stub
	}

	void Component::OnTick(float _deltaTIme) 
	{
		// Stub
	}

	void Component::OnLateTick(float _deltaTime) 
	{
		// Stub
	}

	void Component::OnDisplay(shared<RenderContext> _renderContext)
	{
		// Stub
	}

	void Component::OnRemove() 
	{
		// Stub
	}

	void Component::OnTriggerEnter(shared<RigidBody> _other) 
	{
		// Stub
	}

	void Component::OnTriggerExit(shared<RigidBody> _other) 
	{
		// Stub
	}

	void Component::OnCollisionEnter(shared<RigidBody> _other) 
	{
		// Stub
	}

	void Component::OnCollisionExit(shared<RigidBody> _other)
	{
		// Stub
	}

	void Component::OnDelete() 
	{
		// Stub
	}

	bool Component::NeedsUniqueness() const
	{
		return false;
	}
}