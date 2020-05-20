#pragma once
#include"Actor.h"

class Tower : public Actor {
public:
	Tower(class Game* game);
	void UpdateActor(float deltaTime)override;
private:
	class MoveComponent* m_move;
	float m_nextAttack;
	const float ATTACK_TIME = 2.5f;
	const float ATTACK_RANGE = 100.0f;
};
