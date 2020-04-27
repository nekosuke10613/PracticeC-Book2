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
	//�Q�[���̑��s���w��
	bool m_isRunning;
};