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
	//‹——£‚Ì2æ‚ğŒvZ
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	//”¼Œa‚Ì—Ö‚Ì2æ‚ğŒvZ(radii‚Íradius‚Ì•¡”Œ`)
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}
