#pragma once
#include "Component.h"
#include"CircleComponent.h"
#include"Math.h"

class CollisionComponent : public Component {
public:
	CollisionComponent(class Actor* owner);

	void SetRadius(float radius) { m_radius = radius; }
	float GetRadius()const;
	const Vector2& GetCenter() const;
private:
	float m_radius{ 0.0f };
	
};
bool Intersect(const CollisionComponent& a, const CircleComponent& b);
