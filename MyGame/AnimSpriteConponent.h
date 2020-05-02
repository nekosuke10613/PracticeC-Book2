#pragma once
#include"SpriteComponent.h"
#include<vector>

class AnimSpriteComponent : public SpriteComponent{
public:
	AnimSpriteComponent(class Actor*owner, int drawOrder = 100);
	
	void Update(float deltaTime)override;
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	float GetAnimFPS()const { return m_animFPS; }
	void SetAnimFPS(float fps) { m_animFPS = fps; }
	bool GetIsLoop()const { return m_isLoop; }
	void SetIsLoop(bool isLoop){ m_isLoop = isLoop; }
private:
	std::vector<SDL_Texture*> m_animTextures;
	//現在のフレーム
	float m_currentFrame;
	//アニメーションフレームレート
	float m_animFPS;
	bool m_isLoop;
};