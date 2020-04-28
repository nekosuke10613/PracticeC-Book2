#pragma once
#include "SDL/SDL.h"
#include<unordered_map>
#include<string>
#include<vector>

class Game {
public:
	Game();
	bool Initialize();
	//�I�����m�܂ŃQ�[�����[�v�����s����
	void RunLoop();
	//�I������
	void Shutdown();

	/* Actor�֌W */
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);


private:
	//�Q�[�����[�v�̂��߂̃w���p�[�֐�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
private:
	//�Q�[�����̑S�A�N�^�[�|�C���^�i�[�p
	std::vector<class Actor*>m_actors;
	//�Q�[�����̑҂���Ԃ̃A�N�^�[�Q
	std::vector<class Actor*> m_pendingActors;

private:
	//SDL�����E�B���h�E
	SDL_Window* m_window;
	//SDL�����_���[
	SDL_Renderer* m_renderer;
	//Init����o�߂�������
	Uint32 m_ticksCount;
	//�Q�[���̑��s���w��
	bool m_isRunning;
	//m_actors���X�V���Ă��邩
	bool m_updatetingActors;

private:
	int m_paddleDir;
	Vector2 m_paddlePos;
	Vector2 m_ballPos;
	Vector2 m_ballVel;

};