#pragma once
#include"Actor.h"

//動物の基底クラス
class Animal : public Actor {
public:
	//必要な機能　どうぶつごとのSprite設定　移動速度の設定
	Animal(class Game* game);
	void UpdateActor(float deltaTime) override;
protected:

	float m_speed;


};
