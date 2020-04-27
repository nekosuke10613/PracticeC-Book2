#include"Game.h"

Game::Game():
	m_window(nullptr),
	m_isRunning(true)
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

	//�����_���[�̍쐬
	m_renderer = SDL_CreateRenderer(
		m_window,//�쐬���郌���_���[�̕`��ΏۂƂȂ�E�B���h�E
		-1,		 //�O���t�B�b�N�X�h���C�o�̎w��@�ʏ�́[�P
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	//�����_���[�쐬�����s������
	if (!m_renderer) {
		SDL_Log("Renderer�쐬�Ɏ��s���܂����F%s", SDL_GetError());
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
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
	//�L���[�ɃC�x���g������ΌJ��Ԃ�
	//SDL_PollEvent(SDL_Event�^�̃|�C���^)
	while (SDL_PollEvent(&event)) {
		switch ((event.type))
		{
			//�e��C�x���g�̏���
		case SDL_QUIT: //����{�^���Ȃǂ�Windo�����{�Ƃ�����
			m_isRunning = false;
			break;
		}
	}
	//�L�[�{�[�h�S�̂̏��
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//Escape��������
	if (state[SDL_SCANCODE_ESCAPE]) {
		m_isRunning = false;
	}
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
	//�`��F�̎w��
	SDL_SetRenderDrawColor(
		m_renderer,
		255,	// R
		150,	// G
		150,    // B
		255		// A
	);
	//�o�b�N�o�b�t�@�̃N���A
	SDL_RenderClear(m_renderer);
	//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@������
	SDL_RenderPresent(m_renderer);
}
