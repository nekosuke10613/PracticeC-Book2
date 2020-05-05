#include "Asteroid.h"
#include"Game.h"
#include"SpriteComponent.h"
#include"MoveComponent.h"
#include"Random.h"


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
	mc->SetFOrwardSpeed(150.0f);

	//Circleコンポーネントを作成する

	
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
