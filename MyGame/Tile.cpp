#include "Tile.h"
#include"SpriteComponent.h"
#include"Game.h"

Tile::Tile(Game * game):
	Actor(game)
{
	m_sprite = new SpriteComponent(this);
	UpdateTexture();
}

void Tile::SetTileState(TileState state)
{
	m_tileState = state;
	UpdateTexture();
}

void Tile::ToggleSelect()
{
	m_selected = !m_selected;
	UpdateTexture();
}

void Tile::UpdateTexture()
{
	std::string text;
	switch (m_tileState){
	case EStart:
		text = "Assets/TileTan.png";
		break;
	case EBase:
		text = "Assets/TileGreen.png";
		break;
	case EPath:
		if(m_selected)
			text = "Assets/TileGreySelected.png";
		else
			text = "Assets/TileGrey.png";
		break;
	case EDefault:
	default:
		if(m_selected)
			text = "Assets/TileBrownSelected.png";
		else
			text = "Assets/TileBrown.png";
		break;
	}
	m_sprite->SetTexture(GetGame()->GetTexture(text));
}
