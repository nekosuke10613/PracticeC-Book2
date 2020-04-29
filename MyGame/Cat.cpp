#include "Cat.h"
#include"AnimSpriteConponent.h"
#include"Game.h"
#include"Actor.h"

Cat::Cat(Game * game):Animal(game)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);

	m_speed = 1;
}
