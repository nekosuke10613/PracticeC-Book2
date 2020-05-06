#include "AIComponent.h"
#include"Actor.h"
#include"AIState.h"
#include<SDL/SDL_log.h>

AIComponent::AIComponent(Actor * owner):
	Component(owner)
{
}

void AIComponent::Update(float deltaTime)
{
	if (m_currentState) {
		m_currentState->Update(deltaTime);
	}
}

void AIComponent::ChangeState(const std::string & name)
{
	//現在の状態を抜ける
	if (m_currentState) {
		m_currentState->OnExit();
	}
	//新しい状態を連想配列から探す
	auto iter = m_stateMap.find(name);
	if (iter != m_stateMap.end()) {
		m_currentState = iter->second;
		//新しい状態に入る
		m_currentState->OnEnter();
	}
	else {
		SDL_Log("Could not find AIState %s in state map", name.c_str());
		m_currentState = nullptr;
	}
}

void AIComponent::AddState(AIState * state)
{
	m_stateMap.emplace(state->GetName(), state);
}
