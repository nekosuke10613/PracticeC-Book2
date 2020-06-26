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
	if (m_texture) {
		//テクスチャの幅と高さで矩形をスケーリング
		Matrix4 scalemat = Matrix4::CreateScale(
			static_cast<float>(m_texWidth),
			static_cast<float>(m_texHeight),
			1.0f
		);
		Matrix4 world = scalemat * m_owner->GetWorldTransform();
		//ワールド変換の設定
		shader->SetmatrixUniform("uWorldTransform", world);

		//アクティブなテクスチャを設定
		m_texture->SetActive();
		//矩形を描画
		glDrawElements(
			GL_TRIANGLES,	//描画するポリゴン・プリミティブの種類
			6,				//インデックスバッファにあるインデックスの数
			GL_UNSIGNED_INT,//インデックスの型
			nullptr			//通常はnullptr
		);
	}
}

void SpriteComponent::SetTexture(Texture * texture)
{
	m_texture = texture;
	//テクスチャの幅と高さを得る
	m_texWidth = texture->GetWidth();
	m_texHeight = texture->GetHeight();
}
