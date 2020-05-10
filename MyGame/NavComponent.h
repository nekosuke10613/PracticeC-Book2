#pragma once
#include"MoveComponent.h"
#include"Math.h"

//�A�N�^�[���o�H�ɂ����Ĉړ�����ۂɐ�������������������
class NavComponent : public MoveComponent {
public:
	NavComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime)override;
	void StartPath(const class Tile* start);
	void TurnTo(const Vector2& pos);
private:
	const class Tile* m_nextNode{ nullptr };
};
