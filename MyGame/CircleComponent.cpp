#include "CircleComponent.h"
#include"Actor.h"

CircleComponent::CircleComponent(Actor * owner)
	:Component(owner)
{
}

float CircleComponent::GetRadius() const
{
	return m_owner->GetScale() * m_radius;
}

const Vector2 & CircleComponent::GetCenter() const
{
	return m_owner->GetPosition();
}

bool Intersect(const CircleComponent & a, const CircleComponent & b)
{
	//������2����v�Z
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	//���a�̗ւ�2����v�Z(radii��radius�̕����`)
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
