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
		//�t���[�����[�g�ƃ��^�C���Ɋ�Â���
		//�J�����g�t���[�����X�V����
		m_currentFrame += m_animFPS * deltaTime;

		//�K�v�ɉ����ăJ�����g�t���[���������߂�
		while (m_currentFrame >= m_animTextures.size())
		{
			m_currentFrame -= m_animTextures.size();
		}
		//���݂̃e�N�X�`����ݒ肷��
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
