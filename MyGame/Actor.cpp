#include "Actor.h"
#include"Game.h"
#include"Component.h"
#include<algorithm>

Actor::Actor(Game * game):
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
		ComputeWorldTransform();
		//コンポーネント更新
		UpdateComponents(deltaTime);
		//アクター更新
		UpdateActor(deltaTime);
		ComputeWorldTransform();
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

void Actor::ComputeWorldTransform()
{
	if (m_recomputeWorldTransform) {
		m_recomputeWorldTransform = false;
		//スケーリング → 回転 → 平行移動
		m_worldTransform = Matrix4::CreateScale(m_rotation);
		m_worldTransform *= Matrix4::CreateRotationZ(m_rotation);
		m_worldTransform *= Matrix4::CreateTranslation(
			Vector3(m_position.x, m_position.y, 0.0f)
		);
		//ワールド変換の更新を紺ぷーねんとに通知する
		for (auto comp : m_components) {
			comp->OnUpdateWorldTransform();
		}
	}
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
