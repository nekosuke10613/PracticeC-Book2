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


private:
	//ゲームループのためのヘルパー関数
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
private:
	//ゲーム中の全アクターポインタ格納用
	std::vector<class Actor*>m_actors;
	//ゲーム中の待ち状態のアクター群
	std::vector<class Actor*> m_pendingActors;

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

private:
	int m_paddleDir;
	Vector2 m_paddlePos;
	Vector2 m_ballPos;
	Vector2 m_ballVel;

};