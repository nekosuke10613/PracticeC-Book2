#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
{

}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(m_angularSpeed))
	{
		float rot = m_owner->GetRotation();
		rot += m_angularSpeed * deltaTime;
		m_owner->SetRotation(rot);
	}

	if (!Math::NearZero(m_forwardSpeed))
	{
		Vector2 pos = m_owner->GetPosition();
		pos += m_owner->GetForward() * m_forwardSpeed * deltaTime;

		// (Screen wrapping code only for asteroids)
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		m_owner->SetPosition(pos);
	}
}
