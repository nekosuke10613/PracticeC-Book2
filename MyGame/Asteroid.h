#pragma once
#include"Actor.h"

class Asteroid : public Actor {
public:
	Asteroid(class Game* game);
	~Asteroid();

	class CircleComponent* GetCircle() { return m_circle; }

private:
	class CircleComponent* m_circle{ nullptr };
	
};

