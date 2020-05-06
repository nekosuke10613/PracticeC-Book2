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
	
	//AddForce(Vector2)
private:
	//力の合計から加速度を求める
	//加速度から速度を求める
	//速度から位置を求める


private:
	// 回転を制御する（ラジアン/秒）
	float m_angularSpeed{0.0f};
	// 全身運動を制御する
	float m_forwardSpeed{ 0.0f };

	//physics
	//質量
	float m_mass{ 0.0f };
	//力の合計
	float m_forceSum{ 0.0f };
	//速度
	float velocity{ 0.0f };
};
