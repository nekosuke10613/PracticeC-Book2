#include "Animal.h"

Animal::Animal(Game * game) :
	Actor(game),
	m_speed(1.0f)
{
}

void Animal::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 pos = GetPosition();
	pos.x -= m_speed * deltaTime;
	SetPosition(pos);
}
