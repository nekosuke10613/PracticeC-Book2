#include "NavComponent.h"
#include "Actor.h"

NavComponent::NavComponent(Actor * owner, int updateOrder):
	MoveComponent(owner, updateOrder)
{
}

void NavComponent::Update(float deltaTime)
{
	if (m_nextNode) {
		//次のノードのいる場合はパスに沿って進む
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
	//自分からPosまでのベクトル
	Vector2 dir = pos - m_owner->GetPosition();
	//新しい角度はこのDirのちょうどatan2になる
	//(+yが画面上にあるため、yを否定)
	float angle = Math::Atan2(-dir.y, dir.x);
	m_owner->SetRotation(angle);
	
}
