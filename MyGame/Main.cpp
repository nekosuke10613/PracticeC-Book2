#include "Game.h"

int main(int argc, char** argv) {
	Game game;
	bool success = game.Initialize();
	if (success) {
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}
//規約
//クラス関数GameUpdate()
//メンバ変数m_gameOne
//変数　gameOne