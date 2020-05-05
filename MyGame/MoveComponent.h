#pragma once
#include"Component.h"

class MoveComponent :public Component
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime)override;

	float GetAngularSpeed() const { return m_angularSpeed; }
	float GetForwardSpeed()const { return m_forwardSpeed; }
	void SetAngularSpeed(float speed) { m_angularSpeed = speed; }
	void SetFOrwardSpeed(float speed) { m_forwardSpeed = speed; }

private:
	float m_angularSpeed;
	float m_forwardSpeed;
};
