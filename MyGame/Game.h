#pragma once
#include "SDL/SDL.h"


struct Vector2 {
	float x;
	float y;
};

class Game {
public:
	Game();
	bool Initialize();
	//終了検知までゲームループを実行する
	void RunLoop();
	//終了処理
	void Shutdown();
private:
	//ゲームループのためのヘルパー関数
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

private:
	//SDLが作るウィンドウ
	SDL_Window* m_window;
	//SDLレンダラー
	SDL_Renderer* m_renderer;
	//Initから経過した時間
	Uint32 m_ticksCount;
	//ゲームの続行を指示
	bool m_isRunning;

private:
	Vector2 m_paddlePos;
	Vector2 m_ballPos;

};