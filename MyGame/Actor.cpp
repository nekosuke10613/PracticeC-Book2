#include "Actor.h"
#include"Game.h"
#include"Component.h"
#include<algorithm>

Actor::Actor(Game * game):
	m_state(EActive),
	m_position(Vector2::Zero),
	m_scale(1.0f),
	m_rotation(0.0f),
	m_game(game)
{
	m_game->AddActor(this);
}

Actor::~Actor()
{
	m_game->RemoveActor(this);
	while (!m_components.empty()) {
		delete m_components.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (m_state == EActive) {
		//コンポーネント更新
		UpdateComponents(deltaTime);
		//アクター更新
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : m_components) {
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const uint8_t * keyState)
{
	if (m_state == EActive) {
		for (auto comp : m_components) {
			comp->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t * keyState)
{
}

void Actor::AddComponent(Component * component)
{
	//order少ない順にソート
	int myOrder = component->GetUpdateOrder();
	auto iter = m_components.begin();
	for (; iter != m_components.end(); ++iter) {
		if (myOrder < (*iter)->GetUpdateOrder())
			break;
	}
	//イテレータの位置の前に挿入
	m_components.insert(iter, component);
}

void Actor::RemoveComponent(Component * component)
{
	auto iter = std::find(m_components.begin(), m_components.end(), component);
	if (iter != m_components.end()) {
		m_components.erase(iter);
	}
}
