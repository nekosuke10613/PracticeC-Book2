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
	//�I�����m�܂ŃQ�[�����[�v�����s����
	void RunLoop();
	//�I������
	void Shutdown();
private:
	//�Q�[�����[�v�̂��߂̃w���p�[�֐�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

private:
	//SDL�����E�B���h�E
	SDL_Window* m_window;
	//SDL�����_���[
	SDL_Renderer* m_renderer;
	//Init����o�߂�������
	Uint32 m_ticksCount;
	//�Q�[���̑��s���w��
	bool m_isRunning;

private:
	Vector2 m_paddlePos;
	Vector2 m_ballPos;

};