#pragma once
#include"MoveComponent.h"
#include"Math.h"

//アクターが経路にそって移動する際に正しい方向を向かせる
class NavComponent : public MoveComponent {
public:
	NavComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime)override;
	void StartPath(const class Tile* start);
	void TurnTo(const Vector2& pos);
private:
	const class Tile* m_nextNode{ nullptr };
};
