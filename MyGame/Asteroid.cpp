#include "Asteroid.h"
#include"Game.h"
#include"SpriteComponent.h"
#include"MoveComponent.h"
#include"Random.h"


Asteroid::Asteroid(Game * game):
	Actor(game)
{
	//�����_���Ȉʒu�E�����ŏ���������
	Vector2 randPos = Random::GetVector(Vector2::Zero,
		Vector2(1024.0f, 768.0f));
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	//�X�v���C�g�R���|�[�l���g���쐬���A�e�N�X�`����ݒ肷��
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	//�^���R���|�[�l���g���쐬���A�S�g���x��ݒ肷��
	MoveComponent* mc = new MoveComponent(this);
	mc->SetFOrwardSpeed(150.0f);

	//Circle�R���|�[�l���g���쐬����

	
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
