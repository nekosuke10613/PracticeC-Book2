#pragma once
#include "MoveComponent.h"
#include<cstdint>

class InputComponent : public MoveComponent {
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

public:
	//ゲッター・セッター
	float GetMaxForward() const { return m_maxForwardSpeed; }
	float GetMaxAngular()const { return m_maxAngularSpeed; }
	int GetForwardKey()const { return m_forwardKey; }
	int GetBackKey()const { return m_backKey; }
	int GetBlockwiseKey()const { return m_clockwiseKey; }
	int GetCounterClockwiseKey()const { return m_counterClockwiseKey; }
	
	void SetMaxForwardSpeed(float speed) { m_maxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { m_maxAngularSpeed = speed; }
	void SetForwardKey(int key) { m_forwardKey = key; }
	void SetBackKey(int key) { m_backKey = key; }
	void SetClockwiseKey(int key) { m_clockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { m_counterClockwiseKey = key; }

private:
	//前進・回転の最大速度
	float m_maxForwardSpeed{ 0.0f };
	float m_maxAngularSpeed{ 0.0f };
	//前進・後退のためのキー
	int m_forwardKey{ 0 };
	int m_backKey{ 0 };
	//回転移動のためのキー
	int m_clockwiseKey{ 0 };
	int m_counterClockwiseKey{ 0 };

};