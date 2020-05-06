#pragma once
#include "Actor.h"

class Ship :public Actor {
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime)override;
	void ActorInput(const uint8_t* keyState)override;

	void Init();
	void Dead();

	class CollisionComponent* GetCollision(){ return m_collision; }
private:
	class CollisionComponent* m_collision;
	float m_laserCooldown{ 0.0f };
	Vector2 firstPos{ 500,350 };
	float m_deadTime{ 1.0f };
	bool m_isDead{ false };
};
