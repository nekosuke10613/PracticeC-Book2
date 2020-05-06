#include "CollisionComponent.h"
#include"Actor.h"

CollisionComponent::CollisionComponent(Actor * owner):
	Component(owner)
{
}

float CollisionComponent::GetRadius() const
{
	return m_owner->GetScale() * m_radius;
}

const Vector2 & CollisionComponent::GetCenter() const
{
	return m_owner->GetPosition();
}
bool Intersect(const CollisionComponent& a, const CircleComponent& b) {
	// Calculate distance squared
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	// Calculate sum of radii squared
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
