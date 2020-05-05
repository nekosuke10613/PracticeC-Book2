#pragma once
#include "MoveComponent.h"
#include<cstdint>

class InputComponent : public MoveComponent {
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

public:
	//�Q�b�^�[�E�Z�b�^�[
	float GetMaxForward() const { return m_maxForwardSpeed; }
	float GetMaxAngular()const { return m_maxAngularSpeed; }
	int GetForwardKey()const { return m_forwardKey; }
	int GetBackKey()const { return m_backKey; }
	int GetBlockwiseKey()const { return m_clockwiseKey; }
	int GetCounterClockwiseKey()const { return m_counterClockwiseKey; }
	
	void SetMaxForwardSpeed(float speed) { m_maxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { m_maxAngularSpeed = speed; }
	void SetForwardKey(int key) { m_forwardKey = key; }
	void SetBackKey(int key) { m_backKey = key; }
	void SetClockwiseKey(int key) { m_clockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { m_counterClockwiseKey = key; }

private:
	//�O�i�E��]�̍ő呬�x
	float m_maxForwardSpeed;
	float m_maxAngularSpeed;
	//�O�i�E��ނ̂��߂̃L�[
	int m_forwardKey;
	int m_backKey;
	//��]�ړ��̂��߂̃L�[
	int m_clockwiseKey;
	int m_counterClockwiseKey;

};