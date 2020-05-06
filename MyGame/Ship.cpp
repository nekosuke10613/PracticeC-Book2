#include "Ship.h"
#include"SpriteComponent.h"
#include"InputComponent.h"
#include"Game.h"
#include"Laser.h"

Ship::Ship(Game * game):
	Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime)
{
	m_laserCooldown -= deltaTime;
}

void Ship::ActorInput(const uint8_t * keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && m_laserCooldown <= 0.0f) {
		//レーザーを生成して位置と回転角をShipと合わせる
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());
		//レーザーの冷却期間をリセット
		m_laserCooldown = 0.5f;
	}
}
