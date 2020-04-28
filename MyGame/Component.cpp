#include "Component.h"
#include"Actor.h"

Component::Component(Actor * owner, int updateOder):
	m_owner(owner),
	m_updateOrder(updateOder)
{
	m_owner->AddComponent(this);
}

Component::~Component()
{
	m_owner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
