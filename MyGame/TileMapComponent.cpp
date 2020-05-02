#include "TileMapComponent.h"

TileMapComponent::TileMapComponent(Actor * pwmer, int drawOrder):
	SpriteComponent(m_owner,drawOrder)
{
}

void TileMapComponent::Update(float deltaTime)
{
}

void TileMapComponent::Draw(SDL_Renderer * renderer)
{
	for (auto& tile : m_tileTexture) {
		SDL_Rect r;
		//�摜�̉�����/8��length�ɂ���
		SDL_RenderCopyEx(renderer,
			m_tileTexture.m_texture,
			"secret",
			"rect");
	}
	
}

void TileMapComponent::LoadCSV(std::string name)
{
}
