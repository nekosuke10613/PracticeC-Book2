#include "BGSpriteComponent.h"
#include"Actor.h"

BGSpriteComponent::BGSpriteComponent(Actor * owner, int drawOrder):
	SpriteComponent(owner,drawOrder)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : m_BGTextures) {
		bg.m_offset.x += m_scrollSpeed * deltaTime;
		if (bg.m_offset.x < -m_screenSize.x) {
			bg.m_offset.x = (m_BGTextures.size() - 1) * m_screenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(Shader * renderer)
{
	for (auto& bg : m_BGTextures) {
		SDL_Rect r;
		r.w = static_cast<int>(m_screenSize.x);
		r.h = static_cast<int>(m_screenSize.y);
		r.x = static_cast<int>(m_owner->GetPosition().x - r.w / 2 + bg.m_offset.x);
		r.y = static_cast<int>(m_owner->GetPosition().y - r.h / 2 + bg.m_offset.y);
		
		//SDL_RenderCopy(renderer, bg.m_texture, nullptr, &r);
	}
}

void BGSpriteComponent::SetBGTexture(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures) {
		BGTexture temp;
		temp.m_texture = tex;

		temp.m_offset.x = count * count * m_screenSize.x;
		temp.m_offset.y = 0;
		m_BGTextures.emplace_back(temp);
		count++;
	}
}
