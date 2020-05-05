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
		//幅と高さを所有アクターのスケールで拡縮する
		r.w = static_cast<int>(m_texWidth * m_owner->GetScale());
		r.h = static_cast<int>(m_texHeight * m_owner->GetScale());
		//矩形の中心を所有アクターの位置に合わせる
		r.x = static_cast<int>(m_owner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(m_owner->GetPosition().y - r.w / 2);

		//描画する
		SDL_RenderCopyEx(renderer,
			m_texture,  //描画したいテクスチャ
			nullptr,	//描画したいテクスチャの範囲
			&r,			//出力先の矩形
			-Math::ToDegrees(m_owner->GetRotation()),//変換された回転角
			nullptr,	//回転中心
			SDL_FLIP_NONE);  //反転方向
	}
}

void SpriteComponent::SetTexture(SDL_Texture * texture)
{
	m_texture = texture;
	//テクスチャの幅と高さを得る
	SDL_QueryTexture(texture, nullptr, nullptr,
		&m_texWidth, &m_texHeight);
}
