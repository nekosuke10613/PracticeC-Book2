#include"Game.h"

const int THICKNESS = 15;
const float PADDLE_H = 100.0f;

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
	m_paddlePos.x = 10.0f;
	m_paddlePos.y = 720.0f / 2.0f;
	m_ballPos.x = 1280.0f / 2.0f;
	m_ballPos.y = 720.0f / 2.0f;
	m_ballVel.x = -200.0f;
	m_ballVel.y = 235.0f;

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
	m_paddleDir = 0;
	if (state[SDL_SCANCODE_W])
		m_paddleDir -= 1;
	if (state[SDL_SCANCODE_S])
		m_paddleDir += 1;
}

void Game::UpdateGame()
{
	//フレーム制限　フレーム間少なくとも必ず～ms経過させたい
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount = 16));

	//deltaTimeは前のフレームとの時刻の差を秒に変換した値
	float deltaTime = (SDL_GetTicks() - m_ticksCount) / 1000.0f;

	//deltaTimeを最大値で制限する（ブレークポイント等対策）
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	//時刻を更新（次フレーム用）
	m_ticksCount = SDL_GetTicks();//SDL_Initから経過した時間

	//ゲーム処理
	if (m_paddleDir != 0) {
		//移動
		m_paddlePos.y += m_paddleDir * 300.0f * deltaTime;
		//パドルが画面から出ないようにする
		if (m_paddlePos.y < (PADDLE_H / 2.0f + THICKNESS))
			m_paddlePos.y = PADDLE_H / 2.0f - THICKNESS;
		else if (m_paddlePos.y > (720.0f - PADDLE_H / 2.0f - THICKNESS)) 
			m_paddlePos.y = 720.0f - PADDLE_H / 2.0f - THICKNESS;
		
	}

	//ボール位置更新
	m_ballPos.x += m_ballVel.x * deltaTime;
	m_ballPos.y += m_ballVel.y * deltaTime;

	//
	float diff = m_paddlePos.y - m_ballPos.y;
	if (diff <= PADDLE_H / 2.0f &&
		m_ballPos.x <= 25.0f && m_ballPos.x >= 20.0f &&
		m_ballVel.x < 0.0f) {
		m_ballVel.x *= -1.0f;
	}
	else if (m_ballPos.x <= 0.0f)
		m_isRunning = false;
	else if (m_ballPos.x >= (1280.0f - THICKNESS) && m_ballVel.x > 0.0f)
		m_ballVel.x *= -1.0f;
		
		
	//
	if (m_ballPos.y <= THICKNESS && m_ballVel.y < 0.0f) {
		m_ballVel.y *= 1;
	}
	else if (m_ballPos.y >= (720 - THICKNESS) && m_ballVel.y > 0.0f)
		m_ballVel.y *= -1;
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

	//ゲームの処理

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	//上壁
	SDL_Rect wall{
		0,		//左上隅のｘ
		0,		//左上隅のｙ
		1280,	//幅
		THICKNESS //高さ
	};
	SDL_RenderFillRect(m_renderer, &wall);
	//下壁
	wall.y = 720 - THICKNESS;
	SDL_RenderFillRect(m_renderer, &wall);
	//右壁
	wall.x = 1280 - THICKNESS;
	wall.y = 0;
	wall.w = THICKNESS;
	wall.h = 1024;
	SDL_RenderFillRect(m_renderer, &wall);

	//パドル描画
	SDL_Rect paddle{
		//static_cast float→intにしている
		static_cast<int>(m_paddlePos.x),
		static_cast<int>(m_paddlePos.y - PADDLE_H / 2),
		THICKNESS,
		static_cast<int>(PADDLE_H),
	};
	SDL_RenderFillRect(m_renderer, &paddle);

	//ボール描画
	SDL_Rect ball{
		//static_cast float→intにしている
		static_cast<int>(m_ballPos.x - THICKNESS / 2),
		static_cast<int>(m_ballPos.y - THICKNESS / 2),
		THICKNESS,
		THICKNESS,
	};
	SDL_RenderFillRect(m_renderer, &ball);

	//フロントバッファとバックバッファを交換
	SDL_RenderPresent(m_renderer);
}
