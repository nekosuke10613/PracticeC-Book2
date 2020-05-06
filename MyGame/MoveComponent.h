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
	
	//AddForce(Vector2)
private:
	//�͂̍��v��������x�����߂�
	//�����x���瑬�x�����߂�
	//���x����ʒu�����߂�


private:
	// ��]�𐧌䂷��i���W�A��/�b�j
	float m_angularSpeed{0.0f};
	// �S�g�^���𐧌䂷��
	float m_forwardSpeed{ 0.0f };

	//physics
	//����
	float m_mass{ 0.0f };
	//�͂̍��v
	float m_forceSum{ 0.0f };
	//���x
	float velocity{ 0.0f };
};
