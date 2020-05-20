#include "Asteroid.h"
#include"Game.h"
#include"SpriteComponent.h"
#include"MoveComponent.h"
#include"Random.h"
#include"CircleComponent.h"
#include"AIComponent.h"
#include"AIState.h"


Asteroid::Asteroid(Game * game):
	Actor(game)
{
	//ランダムな位置・向きで初期化する
	Vector2 randPos = Random::GetVector(Vector2::Zero,
		Vector2(1024.0f, 768.0f));
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	//スプライトコンポーネントを作成し、テクスチャを設定する
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//運動コンポーネントを作成し、全身速度を設定する
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	//Circleコンポーネントを作成する
	m_circle = new CircleComponent(this);
	m_circle->SetRadius(40.0f);

	AIComponent* ac = new AIComponent(this);
	ac->AddState(new AIPatrol(ac));
	ac->AddState(new AIAttack(ac));
	ac->AddState(new AIDeath(ac));
	//stringで指定するの嫌い
	ac->ChangeState("Patrol");
	
	//game->AddAsteroid(this);

}

Asteroid::~Asteroid()
{
	//GetGame()->RemoveAsteroid(this);
}
