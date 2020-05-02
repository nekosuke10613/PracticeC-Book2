#pragma once
#include"SpriteComponent.h"
#include <vector>
#include"Math.h"

class TileMapComponent : public SpriteComponent {
public:
	TileMapComponent(class Actor* pwmer, int drawOrder = 10);

	void Update(float deltaTime)override;
	void Draw(SDL_Renderer* renderer)override;

	void LoadCSV(std::string name);

	void SetTileNum(int num) { m_tileNum = num; }
	int GetTileNum() { return m_tileNum; }
	void SetSplitNum(int num) { m_SplitNum = num; }
	int GetSplitNum() { return m_SplitNum; }


	private:
		struct TileMapTexture {
			SDL_Texture* m_texture;
			
		};
		std::vector<TileMapTexture>m_tileTexture;
		int m_tileNum;
		int m_SplitNum;//‰¡‚Ì•ªŠ„”
		float m_tileLength;

	
};
