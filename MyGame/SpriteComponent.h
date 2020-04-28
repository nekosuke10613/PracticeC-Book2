#pragma once
#include"Component.h"
#include"SDL/SDL.h"

class SpriteComponent : public Component{

public:
	//�`�揇�����Ⴂ�قǉ����ɒu�����
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	/* �Q�b�^�[�E�Z�b�^�[ */
	int GetDrawOrder()const { return m_drawOrder; }
	int GetTexHeight()const { return m_texHeight; }
	int GetTexWidth()const { return m_texWidth; }

protected:
	SDL_Texture* m_texture;
	int m_drawOrder;
	int m_texWidth;
	int m_texHeight;

};
