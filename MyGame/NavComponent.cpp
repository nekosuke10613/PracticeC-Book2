#include "NavComponent.h"
#include "Actor.h"

NavComponent::NavComponent(Actor * owner, int updateOrder):
	MoveComponent(owner, updateOrder)
{
}

void NavComponent::Update(float deltaTime)
{
	if (m_nextNode) {
		//���̃m�[�h�̂���ꍇ�̓p�X�ɉ����Đi��
		Vector2 diff = m_owner->GetPosition() - m_nextNode->GetPosition();
		if (Math::NearZero(diff.Length(), 2.0f)) {
			m_nextNode = m_nextNode->GetParent();
			TurnTo(m_nextNode->GetPosition());
		}
	}
	MoveComponent::Update(deltaTime);
}

void NavComponent::StartPath(const Tile * start)
{
	m_nextNode = start->GetParent();
	TurnTo(m_nextNode->GetPosition());
}

void NavComponent::TurnTo(const Vector2 & pos)
{
	//��������Pos�܂ł̃x�N�g��
	Vector2 dir = pos - m_owner->GetPosition();
	//�V�����p�x�͂���Dir�̂��傤��atan2�ɂȂ�
	//(+y����ʏ�ɂ��邽�߁Ay��ے�)
	float angle = Math::Atan2(-dir.y, dir.x);
	m_owner->SetRotation(angle);
	
}
