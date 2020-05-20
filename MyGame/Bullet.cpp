#include "Bullet.h"
#include"SpriteComponent.h"
#include"MoveComponent.h"
#include"CircleComponent.h"
#include"Game.h"
#include"Enemy.h"

Bullet::Bullet(Game * game) :
	Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Projectile.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(400.0f);

	m_circle = new CircleComponent(this);
	m_circle->SetRadius(5.0f);

	m_liveTime = 1.0f;
}

void Bullet::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	for (Enemy* e : GetGame()->GetEnemies()) {
		if (Intersect(*m_circle, *(e->GetCircle()))) {
			e->SetState(EDead);
			SetState(EDead);
			break;
		}
	}
	m_liveTime -= deltaTime;
	if (m_liveTime <= 0.0f) {
		SetState(EDead);
	}
}
