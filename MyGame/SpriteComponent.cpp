#include "SpriteComponent.h"
#include"Texture.h"
#include"Shader.h"
#include"Actor.h"
#include"Game.h"

SpriteComponent::SpriteComponent(Actor * owner, int drawOrder):
	Component(owner),
	m_drawOrder(drawOrder)
{
	m_owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	m_owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader*  shader)
{
	//�e�N�X�`���̕��ƍ����ŋ�`���X�P�[�����O
	Matrix4 scalemat = Matrix4::CreateScale(
		static_cast<float>(m_texWidth),
		static_cast<float>(m_texHeight),
		1.0f
	);
	Matrix4 world = scalemat * m_owner->GetWorldTransform();
	//���[���h�ϊ��̐ݒ�
	shader->SetmatrixUniform("uWorldTransform", world);

	//��`��`��
	glDrawElements(
		GL_TRIANGLES,	//�`�悷��|���S���E�v���~�e�B�u�̎��
		6,				//�C���f�b�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐�
		GL_UNSIGNED_INT,//�C���f�b�N�X�̌^
		nullptr			//�ʏ��nullptr
	);
}

void SpriteComponent::SetTexture(SDL_Texture * texture)
{
	m_texture = texture;
	//�e�N�X�`���̕��ƍ����𓾂�
	SDL_QueryTexture(texture, nullptr, nullptr,
		&m_texWidth, &m_texHeight);
}
