#include"Game.h"

Game::Game():
	m_window(nullptr),
	m_isRunning(nullptr)
{
}

bool Game::Initialize()
{//����������true ���s������false

	//�����F�������t���O�Ƀr�b�g�a�i�@�r�f�I�T�u�V�X�e���j
	//���@
	//SDK_INIT_AUDIO�@�I�[�f�B�I�f�o�C�X�̊Ǘ��Đ��^��
	//SDL_INIT_VIDEO�@�r�f�I�T�u�V�X�e��
	//SDL_INIT_HAPTIC�@�t�H�[�X�t�B�[�h�o�b�N(�U���Ȃ�)�T�u�V�X�e��
	//SDL_INIT�QGAMECONTROLLER�@�R���g���[�����̓f�o�C�X���T�|�[�gs�����߂̃T�u�V�X�e��
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	//SDL�����������s������
	if (sdlResult != 0) {
		SDL_Log("SDL ���������ł��܂���F%s", SDL_GetError());
		return false;
	}
	//Window�쐬
	//SDL_WINDOW_FULLSCREEN �t���X�N���[�����[�h���g��
	//SDL_WINDOW_FULLSCREEN_DESCTOP�@���݂̃f�X�N�g�b�v�̉𑜓x�Ńt���X�N���[�����[�h���g���i���ƍ����̃p�����[�^�����j
	//SDL_WINDOW_OPENGL�@OpenGL���g��
	//SDL_WINDOW_RESIZABLE�@���[�U�[���E�B���h�E�̑傫����ς�����
	m_window = SDL_CreateWindow(
		"MagicGame",//Window�̃^�C�g��
		100,		//�E�B���h�E���[����X���W
		100,		//�E�B���h�E���[���̂����W
		1280,		//�E�B���h�E�̕�
		720,		//�E�B���h�E�̍���
		0			//�E�B���h�E�쐬�t���O(�ݒ肵�Ȃ����͂O)
	);
	//�E�B���h�E�쐬�����s������(���s������nullptr)
	if (!m_window) {
		SDL_Log("Window�쐬�Ɏ��s���܂����F%s", SDL_GetError());
		return false;
	}

	//�����܂ŗ����琬��
	return true;
}

void Game::RunLoop()
{
	//�V���O���X���b�h
	while (m_isRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	//Window��j������
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::ProcessInput()
{
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}
