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
	//�I�����m�܂ŃQ�[�����[�v�����s����
	void RunLoop();
	//�I������
	void Shutdown();

	/* Actor�֌W */
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	/* Sprite�֌W */
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);
	
	//�Q�[���p
	class Grid* GetGrid() { return m_grid; }
	std::vector<class Enemy*>& GetEnemies() { return m_enemys; }
	class Enemy* GetNearestEnemy(const Vector2& pos);

private:
	//�Q�[�����[�v�̂��߂̃w���p�[�֐�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
private:
	//�e�N�X�`�����\�[�Xmap
	std::unordered_map<std::string, SDL_Texture*> m_texture;

	//�Q�[�����̑S�A�N�^�[�|�C���^�i�[�p
	std::vector<class Actor*>m_actors;
	//�Q�[�����̑҂���Ԃ̃A�N�^�[�Q
	std::vector<class Actor*> m_pendingActors;

	//�Q�[�����S�X�v���C�g�R���|�[�l���g
	std::vector<class SpriteComponent*> m_sprite;

private:
	//SDL�����E�B���h�E
	SDL_Window* m_window{ nullptr };
	//SDL�����_���[
	SDL_Renderer* m_renderer{ nullptr };
	//Init����o�߂�������
	Uint32 m_ticksCount;
	//�Q�[���̑��s���w��
	bool m_isRunning{ true };
	//m_actors���X�V���Ă��邩
	bool m_updatetingActors{ false };

	//�Q�[���p
	std::vector<class Enemy*> m_enemys;
	class Grid* m_grid;
	float m_nextEnemy;


};