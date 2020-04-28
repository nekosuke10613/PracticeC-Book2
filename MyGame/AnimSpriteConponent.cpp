#include "AnimSpriteConponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor * owner, int drawOrder):
	SpriteComponent(owner,drawOrder),
	m_currentFrame(0.0f),
	m_animFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (m_animTextures.size() > 0) {
		//フレームレートとΔタイムに基づいて
		//カレントフレームを更新する
		m_currentFrame += m_animFPS * deltaTime;

		//必要に応じてカレントフレームを巻き戻す
		while (m_currentFrame >= m_animTextures.size())
		{
			m_currentFrame -= m_animTextures.size();
		}
		//現在のテクスチャを設定する
		SetTexture(m_animTextures[static_cast<int>(m_currentFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	m_animTextures = textures;
	if (m_animTextures.size() > 0) {
		m_currentFrame = 0.0f;
		SetTexture(m_animTextures[0]);
	}
}
