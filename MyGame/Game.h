#pragma once
#include "SDL/SDL.h"
#include<unordered_map>
#include<string>
#include<vector>

class Game {
public:
	Game();
	bool Initialize();
	//終了検知までゲームループを実行する
	void RunLoop();
	//終了処理
	void Shutdown();

	/* Actor関係 */
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	/* Sprite関係 */
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);
	
	//ゲーム用
	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return m_asteroids; }


private:
	//ゲームループのためのヘルパー関数
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
private:
	//テクスチャリソースmap
	std::unordered_map<std::string, SDL_Texture*> m_texture;

	//ゲーム中の全アクターポインタ格納用
	std::vector<class Actor*>m_actors;
	//ゲーム中の待ち状態のアクター群
	std::vector<class Actor*> m_pendingActors;

	//ゲーム中全スプライトコンポーネント
	std::vector<class SpriteComponent*> m_sprite;

private:
	//SDLが作るウィンドウ
	SDL_Window* m_window;
	//SDLレンダラー
	SDL_Renderer* m_renderer;
	//Initから経過した時間
	Uint32 m_ticksCount;
	//ゲームの続行を指示
	bool m_isRunning;
	//m_actorsを更新しているか
	bool m_updatetingActors;

	//ゲーム用
	class Ship* m_ship;
	std::vector<class Asteroid*> m_asteroids;


};