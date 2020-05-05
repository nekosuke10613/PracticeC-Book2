#include "SpriteComponent.h"
#include"Actor.h"
#include"Game.h"

SpriteComponent::SpriteComponent(Actor * owner, int drawOrder):
	Component(owner),
	m_texture(nullptr),
	m_drawOrder(drawOrder),
	m_texWidth(0),
	m_texHeight(0)
{
	m_owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	m_owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer * renderer)
{
	if (m_texture) {
		SDL_Rect r;
		//���ƍ��������L�A�N�^�[�̃X�P�[���Ŋg�k����
		r.w = static_cast<int>(m_texWidth * m_owner->GetScale());
		r.h = static_cast<int>(m_texHeight * m_owner->GetScale());
		//��`�̒��S�����L�A�N�^�[�̈ʒu�ɍ��킹��
		r.x = static_cast<int>(m_owner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(m_owner->GetPosition().y - r.w / 2);

		//�`�悷��
		SDL_RenderCopyEx(renderer,
			m_texture,  //�`�悵�����e�N�X�`��
			nullptr,	//�`�悵�����e�N�X�`���͈̔�
			&r,			//�o�͐�̋�`
			-Math::ToDegrees(m_owner->GetRotation()),//�ϊ����ꂽ��]�p
			nullptr,	//��]���S
			SDL_FLIP_NONE);  //���]����
	}
}

void SpriteComponent::SetTexture(SDL_Texture * texture)
{
	m_texture = texture;
	//�e�N�X�`���̕��ƍ����𓾂�
	SDL_QueryTexture(texture, nullptr, nullptr,
		&m_texWidth, &m_texHeight);
}
