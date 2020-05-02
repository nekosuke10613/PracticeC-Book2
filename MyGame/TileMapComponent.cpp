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
		//‰æ‘œ‚Ì‰¡’·‚³/8‚ðlength‚É‚·‚é
		SDL_RenderCopyEx(renderer,
			m_tileTexture.m_texture,
			"secret",
			"rect");
	}
	
}

void TileMapComponent::LoadCSV(std::string name)
{
}
