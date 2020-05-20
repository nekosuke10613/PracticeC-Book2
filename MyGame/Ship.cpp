#include "Ship.h"
#include"SpriteComponent.h"
#include"InputComponent.h"
#include"CollisionComponent.h"
#include"Game.h"
#include"Laser.h"
#include"Asteroid.h"

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

	m_collision = new CollisionComponent(this);
	m_collision->SetRadius(40.0f);
}

void Ship::UpdateActor(float deltaTime)
{
	//���[�U�[�̗�p����
	m_laserCooldown -= deltaTime;
	//覐΂Ƃ̏Փ�
	//for (auto ast : GetGame()->GetAsteroids()) {
	//	if (Intersect(*m_collision, *(ast->GetCircle()))) {
	//		//�����������̏���
	//		Dead();
	//		break;
	//	}
	//}
	
	if (m_isDead) {
		m_deadTime -= deltaTime;
		if (m_deadTime < 0) {
			m_deadTime = 5.0f;
			m_isDead = false;
			Init();
		}
	}

}

void Ship::ActorInput(const uint8_t * keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && m_laserCooldown <= 0.0f) {
		//���[�U�[�𐶐����Ĉʒu�Ɖ�]�p��Ship�ƍ��킹��
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());
		//���[�U�[�̗�p���Ԃ����Z�b�g
		m_laserCooldown = 0.5f;
	}
}

void Ship::Init()
{
	SetState(EActive);
	SetPosition(firstPos);
	SetRotation(0);
}

void Ship::Dead()
{
	m_isDead = true;
	SetState(EPaused);
	Init();
}
