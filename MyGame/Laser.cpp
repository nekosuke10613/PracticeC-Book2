#include "Laser.h"
#include"SpriteComponent.h"
#include"MoveComponent.h"
#include"CircleComponent.h"
#include"Game.h"
#include"Asteroid.h"

Laser::Laser(Game * game) :
	Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	m_circle = new CircleComponent(this);
	m_circle->SetRadius(11.0f);

}

void Laser::UpdateActor(float deltaTime)
{
	m_deathTimer -= deltaTime;
	if (m_deathTimer <= 0.0f)
		SetState(EDead);
	else
	{
		//���f���ƌ������邩�H
		//for (auto ast : GetGame()->GetAsteroids()) {
		//	if (Intersect(*m_circle, *(ast->GetCircle())))
		//	{
		//		//���[�U�[�����f���ƌ���������
		//		//���[�U�[�����f����������
		//		SetState(EDead);
		//		ast->SetState(EDead);
		//		break;
		//	}
		//
		//}
	}
}
