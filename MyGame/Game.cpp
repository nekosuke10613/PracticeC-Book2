#include"Game.h"
//#include"SDL/SDL_image.h"
#include<GL/glew.h>
#include<algorithm>

//OpenGL
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"

//Actor
#include"Actor.h"
#include"Grid.h"
#include"Enemy.h"
#include"Random.h"

//Component
#include"SpriteComponent.h"
#include"AIComponent.h"
#include"AIState.h"


Game::Game()
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

	/* OpenGLウィンドウの属性を指定(必ずウィンドウ作成前に行う) */
	//コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//バージョン3.3指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//RGBA各チャンネル8ビットのカラーバッファを使う
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//ダブルバッファを有効にする
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//ハードウェアアクセラレーションを使う
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);


	/* Window作成 */
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
		SDL_WINDOW_OPENGL			//ウィンドウ作成フラグ(設定しない時は０)
	);
	//ウィンドウ作成が失敗したか(失敗したらnullptr)
	if (!m_window) {
		SDL_Log("Window作成に失敗しました：%s", SDL_GetError());
		return false;
	}

	//OpenGL コンテキストの作成
	m_context = SDL_GL_CreateContext(m_window);
	//GLEWの初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	

	//一部のプラットフォームでは、GLEWは無害なエラーコードを出力します。
	glGetError();
	//コンパイル済シェーダーのロード
	if (!LoadShaders()) {
		SDL_Log("Failed to load shaders.");
		return false;
	}

	//Quadにスプライトを描画したものを作成
	CreateSpriteVerts();

	//レンダラーの作成
	//m_renderer = SDL_CreateRenderer(
	//	m_window,//作成するレンダラーの描画対象となるウィンドウ
	//	-1,		 //グラフィックスドライバの指定　通常はー１
	//	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	//);
	//レンダラー作成が失敗したか
	/*if (!m_renderer) {
		SDL_Log("Renderer作成に失敗しました：%s", SDL_GetError());
		return false;
	}*/
	/*if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("SDL_Imageの作成に失敗しました:%s", SDL_GetError());
		return false;
	}*/
	//Random::Init();

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
	//---------ゲーム固有入力--------------
	if (state[SDL_SCANCODE_B]) {
		m_grid->BuildTower();
	}
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT) {
		m_grid->ProcessClick(x, y);
	}
	//-----------------------


	m_updatetingActors = true;
	for (auto actor : m_actors) {
		actor->ProcessInput(state);
	}
	m_updatetingActors = false;
}
void Game::UpdateGame()
{
	//フレーム制限　フレーム間少なくとも必ず〜ms経過させたい
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
		pending->ComputeWorldTransform();
		m_actors.emplace_back(pending);
		
	}
	m_pendingActors.clear();

	//死亡状態のアクターをvector仮入れ
	std::vector<Actor*> deadActors;
	for (auto actor : m_actors) {
		if (actor->GetState() == Actor::EDead) {
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
	//クリアカラーを指定
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	//カラーバッファをクリア
	glClear(GL_COLOR_BUFFER_BIT);

	//全てのSpriteComponentを描画する
	//カラーバッファでαブレンディングを有効にする
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//スプライトシェーダーと頂点配列オブジェクトをアクティブ化
	m_spriteShader->SetActive();
	m_spriteVerts->SetActive();

	//全てのスプライトを描画
	for (auto sprite : m_sprite)
	{
		sprite->Draw(m_spriteShader);
	}

	//バッファを交換。これでシーンが表示される
	SDL_GL_SwapWindow(m_window);
}
bool Game::LoadShaders()
{
	m_spriteShader = new Shader();
	if (!m_spriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag")) {
		return false;
	}
	m_spriteShader->SetActive();
	//view/projection Matrixのセット
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1024.0f, 768.0f);
	m_spriteShader->SetmatrixUniform("uViewProj", viewProj);

	return true;
}
void Game::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
		 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
		 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
		-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};
	m_spriteVerts = new VertexArray(vertices, 4,//Sprite用の4つの頂点
		indices, 6/*4角形を作るには3角形(3頂点)が2つ*/);
}
void Game::LoadData()
{
	m_grid = new Grid(this);

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
		i.second->Unload();
		delete i.second;
	}
	m_texture.clear();

}

Texture * Game::GetTexture(const std::string & fileName)
{
	Texture* tex = nullptr;
	//すでに読み込まれているテクスチャなら検索して持ってくる
	auto iter = m_texture.find(fileName);
	if (iter != m_texture.end()) {
		tex = iter->second;
	}
	else {
		//ファイルをロードする
		tex = new Texture();
		if (tex->Load(fileName)) {
			m_texture.emplace(fileName, tex);
		}
		else {
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}


void Game::Shutdown()
{
	UnloadData();
	delete m_spriteVerts;
	m_spriteShader->Unload();
	delete m_spriteShader;
	//Windowを破棄する
	SDL_GL_DeleteContext(m_context);
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
Enemy * Game::GetNearestEnemy(const Vector2 & pos)
{
	Enemy*best = nullptr;

	if (m_enemys.size() > 0) {
		best = m_enemys[0];

		float bestDistSq = (pos - m_enemys[0]->GetPosition()).LengthSq();
		for (size_t i = 1; i < m_enemys.size(); i++) {
			float newDistSq = (pos - m_enemys[i]->GetPosition()).LengthSq();
			if (newDistSq < bestDistSq) {
				bestDistSq = bestDistSq;
				best = m_enemys[i];
			}
		}
	}

	return best;
}







