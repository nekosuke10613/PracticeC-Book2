#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	// UpdateOrder�̒l���������قǐ�ɍX�V�����
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return m_angularSpeed; }
	float GetForwardSpeed() const { return m_forwardSpeed; }
	void SetAngularSpeed(float speed) { m_angularSpeed = speed; }
	void SetForwardSpeed(float speed) { m_forwardSpeed = speed; }
private:
	// ��]�𐧌䂷��i���W�A��/�b�j
	float m_angularSpeed{0.0f};
	// �S�g�^���𐧌䂷��
	float m_forwardSpeed{ 0.0f };
};
