#include"Game.h"
#include"SDL/SDL_image.h"
#include<algorithm>

//Actor
#include"Actor.h"
#include"Ship.h"
#include"Asteroid.h"
#include"Random.h"

//Component
#include "BGSpriteComponent.h"
#include"SpriteComponent.h"


Game::Game() :
	m_window(nullptr),
	m_renderer(nullptr),
	m_isRunning(true),
	m_updatetingActors(false)
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
	int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
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
		1024,		//ウィンドウの幅
		768,		//ウィンドウの高さ
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
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("SDL_Imageの作成に失敗しました:%s", SDL_GetError());
		return false;
	}
	Random::Init();
	LoadData();

	m_ticksCount = SDL_GetTicks();
	

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
	m_updatetingActors = true;
	for (auto actor : m_actors) {
		actor->ProcessInput(state);
	}
	m_updatetingActors = false;
}
void Game::UpdateGame()
{
	//フレーム制限　フレーム間少なくとも必ず～ms経過させたい
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount + 16));

	//deltaTimeは前のフレームとの時刻の差を秒に変換した値
	float deltaTime = (SDL_GetTicks() - m_ticksCount) / 1000.0f;

	//deltaTimeを最大値で制限する（ブレークポイント等対策）
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	//時刻を更新（次フレーム用）
	m_ticksCount = SDL_GetTicks();//SDL_Initから経過した時間

	/*   アクター関連   */
	//全アクター更新
	m_updatetingActors = true;
	for (auto actor : m_actors) {
		actor->Update(deltaTime);
	}
	m_updatetingActors = false;

	//待ちアクターをm_actorsに移動する
	for (auto pending : m_pendingActors) {
		m_actors.emplace_back(pending);
	}
	m_pendingActors.clear();

	//死亡状態のアクターをvector仮入れ
	std::vector<Actor*> deadActors;
	for (auto actor : m_actors) {
		if (actor->GetScale() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}
	//死亡状態アクターの削除
	for (auto actor : deadActors) {
		delete actor;
	}

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
	// Draw all sprite components
	for (auto sprite : m_sprite)
	{
		sprite->Draw(m_renderer);
	}


	//フロントバッファとバックバッファを交換
	SDL_RenderPresent(m_renderer);
}
void Game::LoadData()
{
	m_ship = new Ship(this);
	m_ship->SetPosition(Vector2(512.0f, 384.0f));
	m_ship->SetRotation(Math::PiOver2);
	// Create asteroids
	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}

}

void Game::UnloadData()
{
	//アクター削除
	while (!m_actors.empty())
	{
		delete m_actors.back();
	}
	//テクスチャの削除
	for (auto i : m_texture) {
		SDL_DestroyTexture(i.second);
	}
	m_texture.clear();

}

SDL_Texture * Game::GetTexture(const std::string & fileName)
{
	SDL_Texture* tex = nullptr;
	//すでに読み込まれているテクスチャなら検索して持ってくる
	auto iter = m_texture.find(fileName);
	if (iter != m_texture.end()) {
		tex = iter->second;
	}
	else {
		//ファイルをロードする
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("テクスチャのロードに失敗しました%s:", fileName.c_str());
			return nullptr;
		}

		//surfaceテクスチャ作成
		tex = SDL_CreateTextureFromSurface(m_renderer, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("surfaceのテクスチャ変換に失敗しました ファイル名:%s", fileName.c_str());
			return nullptr;
		}

		m_texture.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::AddAsteroid(Asteroid * ast)
{
	m_asteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid * ast)
{
	auto iter = std::find(m_asteroids.begin(),
		m_asteroids.end(), ast);
	if (iter != m_asteroids.end()) {
		m_asteroids.erase(iter);
	}
}


void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	//Windowを破棄する
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	
	SDL_Quit();
}

void Game::AddActor(Actor * actor)
{
	//アクターの更新中なら待ちに追加
	if (m_updatetingActors)
		m_pendingActors.emplace_back(actor);
	else
		m_actors.emplace_back(actor);
}

void Game::RemoveActor(Actor * actor)
{
	//子のアクターは待機中か
	auto iter = std::find(m_pendingActors.begin(), m_pendingActors.end(), actor);
	if (iter != m_pendingActors.end()) {
		//vectorの最後に入れ替えてから出す(コピー削除避け)
		std::iter_swap(iter, m_pendingActors.end() - 1);
		m_pendingActors.pop_back();
	}
	//
	iter = std::find(m_actors.begin(), m_actors.end(), actor);
	if(iter != m_actors.end()){
		//vectorの最後に入れ替えてから出す(コピー削除避け)
		std::iter_swap(iter, m_actors.end() - 1);
		m_actors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent * sprite)
{
	//ソート済みの配列で挿入点を見つける
	//（自分よりも順序の高い最初の要素の位置）
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = m_sprite.begin();
	for (; iter != m_sprite.end(); ++iter) {
		if (myDrawOrder < (*iter)->GetDrawOrder())
			break;
	}
	//iter位置の前に要素を挿入
	m_sprite.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent * sprite)
{
	//
	auto iter = std::find(m_sprite.begin(), m_sprite.end(), sprite);
	m_sprite.erase(iter);
}







