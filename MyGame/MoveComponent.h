#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	// UpdateOrderの値が小さいほど先に更新される
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return m_angularSpeed; }
	float GetForwardSpeed() const { return m_forwardSpeed; }
	void SetAngularSpeed(float speed) { m_angularSpeed = speed; }
	void SetForwardSpeed(float speed) { m_forwardSpeed = speed; }
private:
	// 回転を制御する（ラジアン/秒）
	float m_angularSpeed{0.0f};
	// 全身運動を制御する
	float m_forwardSpeed{ 0.0f };
};
