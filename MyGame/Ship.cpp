#include "Ship.h"
#include"AnimSpriteConponent.h"
#include"Game.h"

Ship::Ship(Game * game):
	Actor(game),
	m_rightSpeed(0.0f),
	m_downSpeed(0.0f)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*>anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 pos = GetPosition();
	pos.x += m_rightSpeed * deltaTime;
	pos.y += m_downSpeed * deltaTime;

	if (pos.x < 25.0f)
		pos.x = 25.0f;
	else if (pos.x > 500.0f)
		pos.x = 500.0f;

	if (pos.y < 25.0f)
		pos.y = 25.0f;
	else if (pos.y > 743.0f)
		pos.y = 743.0f;

	SetPosition(pos);

}
void Ship::ProceessKeyboard(const uint8_t * state)
{
	m_rightSpeed = 0.0f;
	m_downSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		m_rightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		m_rightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		m_downSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		m_downSpeed -= 300.0f;
	}
}
