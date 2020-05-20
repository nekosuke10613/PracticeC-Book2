#pragma once
#include"Actor.h"

class Enemy : public Actor {
public:
	Enemy(class Game* game);
	~Enemy();

	void UpdateActor(float deltaTime)override;
	class CircleComponent* GetCircle() { return m_circle; }
private:
	class CircleComponent* m_circle;
};
