#include"Game.h"

Game::Game():
	m_window(nullptr),
	m_isRunning(true)
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

	//レンダラーの作成
	m_renderer = SDL_CreateRenderer(
		m_window,//作成するレンダラーの描画対象となるウィンドウ
		-1,		 //グラフィックスドライバの指定　通常はー１
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	//レンダラー作成が失敗したか
	if (!m_renderer) {
		SDL_Log("Renderer作成に失敗しました：%s", SDL_GetError());
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
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
	//キューにイベントがあれば繰り返す
	//SDL_PollEvent(SDL_Event型のポインタ)
	while (SDL_PollEvent(&event)) {
		switch ((event.type))
		{
			//各種イベントの処理
		case SDL_QUIT: //閉じるボタンなどでWindoｗ閉滋養としたら
			m_isRunning = false;
			break;
		}
	}
	//キーボード全体の状態
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//Escape押したら
	if (state[SDL_SCANCODE_ESCAPE]) {
		m_isRunning = false;
	}
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
	//描画色の指定
	SDL_SetRenderDrawColor(
		m_renderer,
		255,	// R
		150,	// G
		150,    // B
		255		// A
	);
	//バックバッファのクリア
	SDL_RenderClear(m_renderer);
	//フロントバッファとバックバッファを交換
	SDL_RenderPresent(m_renderer);
}
