#include "InputComponent.h"
#include"Actor.h"

InputComponent::InputComponent(Actor * owner):
	MoveComponent(owner),
	m_forwardKey(0),
	m_backKey(0),
	m_clockwiseKey(0),
	m_counterClockwiseKey(0)
{
}

void InputComponent::ProcessInput(const uint8_t * keyState)
{
	//MoveComponent�̂��߂̑O�i���x���v�Z
	float forwardSpeed = 0.0f;
	if (keyState[m_forwardKey])
		forwardSpeed += m_maxForwardSpeed;
	if (keyState[m_backKey])
		forwardSpeed -= m_maxForwardSpeed;
	SetForwardSpeed(forwardSpeed);

	//MoveComponent�̂��߂ɉ�]���x���v�Z
	float angularSpeed  = 0.0f;
	if (keyState[m_clockwiseKey])
		angularSpeed += m_maxAngularSpeed;
	if (keyState[m_counterClockwiseKey])
		angularSpeed -= m_maxAngularSpeed;
	SetAngularSpeed(angularSpeed);
}
