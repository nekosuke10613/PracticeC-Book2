#include"Game.h"

Game::Game():
	m_window(nullptr),
	m_isRunning(nullptr)
{
}

bool Game::Initialize()
{//成功したらtrue 失敗したらfalse

	//引数：初期化フラグにビット和（　ビデオサブシステム）
	//他　
	//SDK_INIT_AUDIO　オーディオデバイスの管理再生録音
	//SDL_INIT_VIDEO　ビデオサブシステム
	//SDL_INIT_HAPTIC　フォースフィードバック(振動など)サブシステム
	//SDL_INIT＿GAMECONTROLLER　コントローラ入力デバイスをサポートsルためのサブシステム
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	//SDL初期化が失敗したか
	if (sdlResult != 0) {
		SDL_Log("SDL を初期化できません：%s", SDL_GetError());
		return false;
	}
	//Window作成
	//SDL_WINDOW_FULLSCREEN フルスクリーンモードを使う
	//SDL_WINDOW_FULLSCREEN_DESCTOP　現在のデスクトップの解像度でフルスクリーンモードを使う（幅と高さのパラメータ無視）
	//SDL_WINDOW_OPENGL　OpenGLを使う
	//SDL_WINDOW_RESIZABLE　ユーザーがウィンドウの大きさを変えられる
	m_window = SDL_CreateWindow(
		"MagicGame",//Windowのタイトル
		100,		//ウィンドウ左端隅のX座標
		100,		//ウィンドウ左端隅のｙ座標
		1280,		//ウィンドウの幅
		720,		//ウィンドウの高さ
		0			//ウィンドウ作成フラグ(設定しない時は０)
	);
	//ウィンドウ作成が失敗したか(失敗したらnullptr)
	if (!m_window) {
		SDL_Log("Window作成に失敗しました：%s", SDL_GetError());
		return false;
	}

	//ここまで来たら成功
	return true;
}

void Game::RunLoop()
{
	//シングルスレッド
	while (m_isRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	//Windowを破棄する
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::ProcessInput()
{
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}
