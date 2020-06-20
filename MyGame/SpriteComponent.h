#pragma once
#include"Component.h"
#include"SDL/SDL.h"

class SpriteComponent : public Component{

public:
	//描画順序が低いほど遠くに置かれる
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(class Shader* shader);
	virtual void SetTexture(SDL_Texture* texture);

	/* ゲッター・セッター */
	int GetDrawOrder()const { return m_drawOrder; }
	int GetTexHeight()const { return m_texHeight; }
	int GetTexWidth()const { return m_texWidth; }

protected:
	SDL_Texture* m_texture{ nullptr };
	int m_drawOrder;
	int m_texWidth{ 0 };
	int m_texHeight{ 0 };

};
