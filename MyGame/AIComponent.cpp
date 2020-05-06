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
	//���݂̏�Ԃ𔲂���
	if (m_currentState) {
		m_currentState->OnExit();
	}
	//�V������Ԃ�A�z�z�񂩂�T��
	auto iter = m_stateMap.find(name);
	if (iter != m_stateMap.end()) {
		m_currentState = iter->second;
		//�V������Ԃɓ���
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
