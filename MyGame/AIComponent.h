#pragma once
#include"Component.h"
#include<unordered_map>
#include<string>

class AIComponent :public Component{
public:
	AIComponent(class Actor* owner);

	void Update(float deltaTime)override;
	void ChangeState(const std::string& name);

	//新たな状態を連想配列に登録する
	void AddState(class AIState* state);
private:
	//状態の名前とAIStateのインスタンスを対応付ける
	std::unordered_map<std::string, class AIState*>m_stateMap;
	//現在の状態
	class AIState* m_currentState{ nullptr };
};
