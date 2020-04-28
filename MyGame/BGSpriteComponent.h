#pragma once
#include"SpriteComponent.h"
#include<vector>
#include"Math.h"

class BGSpriteComponent : public SpriteComponent {
public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);

	void Update(float deltaTime)override;
	void Draw(SDL_Renderer* renderer)override;

	//背景テクスチャのセット
	void SetBGTexture(const std::vector<SDL_Texture*>& texture);
	/* getter/setter */
	void SetScreenSize(const Vector2& size) { m_screenSize = size; }
	void SetScrollSpeed(float speed) { m_scrollSpeed = speed; }
	float GetScrollSpeed()const { return m_scrollSpeed; }

private:
	struct BGTexture {
		SDL_Texture* m_texture;
		Vector2 m_offset;
	};
	std::vector<BGTexture> m_BGTextures;
	Vector2 m_screenSize;
	float m_scrollSpeed;
};
