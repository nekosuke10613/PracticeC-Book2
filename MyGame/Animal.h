#pragma once
#include"Actor.h"

//�����̊��N���X
class Animal : public Actor {
public:
	//�K�v�ȋ@�\�@�ǂ��Ԃ��Ƃ�Sprite�ݒ�@�ړ����x�̐ݒ�
	Animal(class Game* game);
	void UpdateActor(float deltaTime) override;
protected:

	float m_speed;


};
