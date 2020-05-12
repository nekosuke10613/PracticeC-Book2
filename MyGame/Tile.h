#pragma once

#include"Actor.h"
#include<vector>

class Tile : public Actor {
public:
	friend class Grid;
	enum TileState {
		EDefault,
		EPath,
		EStart,
		EBase
	};

	Tile(class Game* game);

	void SetTileState(TileState state);
	TileState GetTileState()const { return m_tileState; }
	void ToggleSelect();
	const Tile* GetParent()const { return m_parent; }

private:
	void UpdateTexture();
private:
	std::vector<Tile*> m_adjacent;
	Tile* m_parent{ nullptr };
	float f{ 0.0f };
	float g{ 0.0f };
	float h{ 0.0f };
	bool m_inOpenSet;
	bool m_inClosedSet;
	bool m_blooked{ false };

private:
	class SpriteComponent* m_sprite{ nullptr };
	TileState m_tileState{ EDefault };
	bool m_selected{ false };

};
