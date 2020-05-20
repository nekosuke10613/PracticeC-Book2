#pragma once
#include "SDL/SDL.h"
#include<unordered_map>
#include<string>
#include<vector>
#include"Math.h"

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
	class Grid* GetGrid() { return m_grid; }
	std::vector<class Enemy*>& GetEnemies() { return m_enemys; }
	class Enemy* GetNearestEnemy(const Vector2& pos);

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
	SDL_Window* m_window{ nullptr };
	//SDLレンダラー
	SDL_Renderer* m_renderer{ nullptr };
	//Initから経過した時間
	Uint32 m_ticksCount;
	//ゲームの続行を指示
	bool m_isRunning{ true };
	//m_actorsを更新しているか
	bool m_updatetingActors{ false };

	//ゲーム用
	std::vector<class Enemy*> m_enemys;
	class Grid* m_grid;
	float m_nextEnemy;


};