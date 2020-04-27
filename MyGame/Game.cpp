#include"Game.h"

const int THICKNESS = 15;
const float PADDLE_H = 100.0f;

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
	m_paddlePos.x = 10.0f;
	m_paddlePos.y = 720.0f / 2.0f;
	m_ballPos.x = 1280.0f / 2.0f;
	m_ballPos.y = 720.0f / 2.0f;
	m_ballVel.x = -200.0f;
	m_ballVel.y = 235.0f;

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
	m_paddleDir = 0;
	if (state[SDL_SCANCODE_W])
		m_paddleDir -= 1;
	if (state[SDL_SCANCODE_S])
		m_paddleDir += 1;
}

void Game::UpdateGame()
{
	//�t���[�������@�t���[���ԏ��Ȃ��Ƃ��K���`ms�o�߂�������
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount = 16));

	//deltaTime�͑O�̃t���[���Ƃ̎����̍���b�ɕϊ������l
	float deltaTime = (SDL_GetTicks() - m_ticksCount) / 1000.0f;

	//deltaTime���ő�l�Ő�������i�u���[�N�|�C���g���΍�j
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	//�������X�V�i���t���[���p�j
	m_ticksCount = SDL_GetTicks();//SDL_Init����o�߂�������

	//�Q�[������
	if (m_paddleDir != 0) {
		//�ړ�
		m_paddlePos.y += m_paddleDir * 300.0f * deltaTime;
		//�p�h������ʂ���o�Ȃ��悤�ɂ���
		if (m_paddlePos.y < (PADDLE_H / 2.0f + THICKNESS))
			m_paddlePos.y = PADDLE_H / 2.0f - THICKNESS;
		else if (m_paddlePos.y > (720.0f - PADDLE_H / 2.0f - THICKNESS)) 
			m_paddlePos.y = 720.0f - PADDLE_H / 2.0f - THICKNESS;
		
	}

	//�{�[���ʒu�X�V
	m_ballPos.x += m_ballVel.x * deltaTime;
	m_ballPos.y += m_ballVel.y * deltaTime;

	//
	float diff = m_paddlePos.y - m_ballPos.y;
	if (diff <= PADDLE_H / 2.0f &&
		m_ballPos.x <= 25.0f && m_ballPos.x >= 20.0f &&
		m_ballVel.x < 0.0f) {
		m_ballVel.x *= -1.0f;
	}
	else if (m_ballPos.x <= 0.0f)
		m_isRunning = false;
	else if (m_ballPos.x >= (1280.0f - THICKNESS) && m_ballVel.x > 0.0f)
		m_ballVel.x *= -1.0f;
		
		
	//
	if (m_ballPos.y <= THICKNESS && m_ballVel.y < 0.0f) {
		m_ballVel.y *= 1;
	}
	else if (m_ballPos.y >= (720 - THICKNESS) && m_ballVel.y > 0.0f)
		m_ballVel.y *= -1;
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

	//�Q�[���̏���

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	//���
	SDL_Rect wall{
		0,		//������̂�
		0,		//������̂�
		1280,	//��
		THICKNESS //����
	};
	SDL_RenderFillRect(m_renderer, &wall);
	//����
	wall.y = 720 - THICKNESS;
	SDL_RenderFillRect(m_renderer, &wall);
	//�E��
	wall.x = 1280 - THICKNESS;
	wall.y = 0;
	wall.w = THICKNESS;
	wall.h = 1024;
	SDL_RenderFillRect(m_renderer, &wall);

	//�p�h���`��
	SDL_Rect paddle{
		//static_cast float��int�ɂ��Ă���
		static_cast<int>(m_paddlePos.x),
		static_cast<int>(m_paddlePos.y - PADDLE_H / 2),
		THICKNESS,
		static_cast<int>(PADDLE_H),
	};
	SDL_RenderFillRect(m_renderer, &paddle);

	//�{�[���`��
	SDL_Rect ball{
		//static_cast float��int�ɂ��Ă���
		static_cast<int>(m_ballPos.x - THICKNESS / 2),
		static_cast<int>(m_ballPos.y - THICKNESS / 2),
		THICKNESS,
		THICKNESS,
	};
	SDL_RenderFillRect(m_renderer, &ball);

	//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@������
	SDL_RenderPresent(m_renderer);
}
