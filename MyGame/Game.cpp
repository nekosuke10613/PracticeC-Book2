#include"Game.h"
//#include"SDL/SDL_image.h"
#include<GL/glew.h>
#include<algorithm>

//OpenGL
#include"VertexArray.h"

//Actor
#include"Actor.h"
#include"Grid.h"
#include"Enemy.h"
#include"Random.h"

//Component
#include"SpriteComponent.h"
#include"AIComponent.h"
#include"AIState.h"


Game::Game()
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
	int sdlResult = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	//SDL�����������s������
	if (sdlResult != 0) {
		SDL_Log("SDL ���������ł��܂���F%s", SDL_GetError());
		return false;
	}

	/* OpenGL�E�B���h�E�̑������w��(�K���E�B���h�E�쐬�O�ɍs��) */
	//�R�AOpenGL�v���t�@�C�����g��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//�o�[�W����3.3�w��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//RGBA�e�`�����l��8�r�b�g�̃J���[�o�b�t�@���g��
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	//�_�u���o�b�t�@��L���ɂ���
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//�n�[�h�E�F�A�A�N�Z�����[�V�������g��
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);


	/* Window�쐬 */
	//SDL_WINDOW_FULLSCREEN �t���X�N���[�����[�h���g��
	//SDL_WINDOW_FULLSCREEN_DESCTOP�@���݂̃f�X�N�g�b�v�̉𑜓x�Ńt���X�N���[�����[�h���g���i���ƍ����̃p�����[�^�����j
	//SDL_WINDOW_OPENGL�@OpenGL���g��
	//SDL_WINDOW_RESIZABLE�@���[�U�[���E�B���h�E�̑傫����ς�����
	m_window = SDL_CreateWindow(
		"MagicGame",//Window�̃^�C�g��
		100,		//�E�B���h�E���[����X���W
		100,		//�E�B���h�E���[���̂����W
		1024,		//�E�B���h�E�̕�
		768,		//�E�B���h�E�̍���
		SDL_WINDOW_OPENGL			//�E�B���h�E�쐬�t���O(�ݒ肵�Ȃ����͂O)
	);
	//�E�B���h�E�쐬�����s������(���s������nullptr)
	if (!m_window) {
		SDL_Log("Window�쐬�Ɏ��s���܂����F%s", SDL_GetError());
		return false;
	}

	//OpenGL �R���e�L�X�g�̍쐬
	m_context = SDL_GL_CreateContext(m_window);
	//GLEW�̏�����
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}
	

	//�ꕔ�̃v���b�g�t�H�[���ł́AGLEW�͖��Q�ȃG���[�R�[�h���o�͂��܂��B
	glGetError();
	//�R���p�C���σV�F�[�_�[�̃��[�h
	if (!LoadShaders()) {
		SDL_Log("Failed to load shaders.");
		return false;
	}

	//Quad�ɃX�v���C�g��`�悵�����̂��쐬
	CreateSpriteVerts();

	//�����_���[�̍쐬
	//m_renderer = SDL_CreateRenderer(
	//	m_window,//�쐬���郌���_���[�̕`��ΏۂƂȂ�E�B���h�E
	//	-1,		 //�O���t�B�b�N�X�h���C�o�̎w��@�ʏ�́[�P
	//	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	//);
	//�����_���[�쐬�����s������
	/*if (!m_renderer) {
		SDL_Log("Renderer�쐬�Ɏ��s���܂����F%s", SDL_GetError());
		return false;
	}*/
	/*if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("SDL_Image�̍쐬�Ɏ��s���܂���:%s", SDL_GetError());
		return false;
	}*/
	//Random::Init();

	LoadData();

	m_ticksCount = SDL_GetTicks();
	

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
	//---------�Q�[���ŗL����--------------
	if (state[SDL_SCANCODE_B]) {
		m_grid->BuildTower();
	}
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT) {
		m_grid->ProcessClick(x, y);
	}
	//-----------------------


	m_updatetingActors = true;
	for (auto actor : m_actors) {
		actor->ProcessInput(state);
	}
	m_updatetingActors = false;
}
void Game::UpdateGame()
{
	//�t���[�������@�t���[���ԏ��Ȃ��Ƃ��K���`ms�o�߂�������
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksCount + 16));

	//deltaTime�͑O�̃t���[���Ƃ̎����̍���b�ɕϊ������l
	float deltaTime = (SDL_GetTicks() - m_ticksCount) / 1000.0f;

	//deltaTime���ő�l�Ő�������i�u���[�N�|�C���g���΍�j
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	//�������X�V�i���t���[���p�j
	m_ticksCount = SDL_GetTicks();//SDL_Init����o�߂�������

	/*   �A�N�^�[�֘A   */
	//�S�A�N�^�[�X�V
	m_updatetingActors = true;
	for (auto actor : m_actors) {
		actor->Update(deltaTime);
	}
	m_updatetingActors = false;

	//�҂��A�N�^�[��m_actors�Ɉړ�����
	for (auto pending : m_pendingActors) {
		m_actors.emplace_back(pending);
	}
	m_pendingActors.clear();

	//���S��Ԃ̃A�N�^�[��vector������
	std::vector<Actor*> deadActors;
	for (auto actor : m_actors) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}
	//���S��ԃA�N�^�[�̍폜
	for (auto actor : deadActors) {
		delete actor;
	}

}

void Game::GenerateOutput()
{
	//�N���A�J���[���w��
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	//�J���[�o�b�t�@���N���A
	glClear(GL_COLOR_BUFFER_BIT);

	//�S�Ă�SpriteComponent��`�悷��
	//�J���[�o�b�t�@�Ń��u�����f�B���O��L���ɂ���
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//shader / vao�@��L���ɂ���


	//�o�b�t�@�������B����ŃV�[�����\�������
	SDL_GL_SwapWindow(m_window);
}
bool Game::LoadShaders()
{
	return false;
}
void Game::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
		 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
		 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
		-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};
	m_spriteVerts = new VertexArray(vertices, 4,//Sprite�p��4�̒��_
		indices, 6/*4�p�`�����ɂ�3�p�`(3���_)��2��*/);
}
void Game::LoadData()
{
	m_grid = new Grid(this);

}

void Game::UnloadData()
{
	//�A�N�^�[�폜
	while (!m_actors.empty())
	{
		delete m_actors.back();
	}
	//�e�N�X�`���̍폜
	for (auto i : m_texture) {
		SDL_DestroyTexture(i.second);
	}
	m_texture.clear();

}

SDL_Texture * Game::GetTexture(const std::string & fileName)
{
	SDL_Texture* tex = nullptr;
	//���łɓǂݍ��܂�Ă���e�N�X�`���Ȃ猟�����Ď����Ă���
	auto iter = m_texture.find(fileName);
	if (iter != m_texture.end()) {
		tex = iter->second;
	}
	else {
		//�t�@�C�������[�h����
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("�e�N�X�`���̃��[�h�Ɏ��s���܂���%s:", fileName.c_str());
			return nullptr;
		}

		//surface�e�N�X�`���쐬
		//tex = SDL_CreateTextureFromSurface(m_renderer, surf);
		/*SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("surface�̃e�N�X�`���ϊ��Ɏ��s���܂��� �t�@�C����:%s", fileName.c_str());
			return nullptr;
		}*/

		m_texture.emplace(fileName.c_str(), tex);
	}
	return tex;
}


void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	//Window��j������
	//SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	
	SDL_Quit();
}

void Game::AddActor(Actor * actor)
{
	//�A�N�^�[�̍X�V���Ȃ�҂��ɒǉ�
	if (m_updatetingActors)
		m_pendingActors.emplace_back(actor);
	else
		m_actors.emplace_back(actor);
}

void Game::RemoveActor(Actor * actor)
{
	//�q�̃A�N�^�[�͑ҋ@����
	auto iter = std::find(m_pendingActors.begin(), m_pendingActors.end(), actor);
	if (iter != m_pendingActors.end()) {
		//vector�̍Ō�ɓ���ւ��Ă���o��(�R�s�[�폜����)
		std::iter_swap(iter, m_pendingActors.end() - 1);
		m_pendingActors.pop_back();
	}
	//
	iter = std::find(m_actors.begin(), m_actors.end(), actor);
	if(iter != m_actors.end()){
		//vector�̍Ō�ɓ���ւ��Ă���o��(�R�s�[�폜����)
		std::iter_swap(iter, m_actors.end() - 1);
		m_actors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent * sprite)
{
	//�\�[�g�ς݂̔z��ő}���_��������
	//�i�������������̍����ŏ��̗v�f�̈ʒu�j
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = m_sprite.begin();
	for (; iter != m_sprite.end(); ++iter) {
		if (myDrawOrder < (*iter)->GetDrawOrder())
			break;
	}
	//iter�ʒu�̑O�ɗv�f��}��
	m_sprite.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent * sprite)
{
	//
	auto iter = std::find(m_sprite.begin(), m_sprite.end(), sprite);
	m_sprite.erase(iter);
}
Enemy * Game::GetNearestEnemy(const Vector2 & pos)
{
	Enemy*best = nullptr;

	if (m_enemys.size() > 0) {
		best = m_enemys[0];

		float bestDistSq = (pos - m_enemys[0]->GetPosition()).LengthSq();
		for (size_t i = 1; i < m_enemys.size(); i++) {
			float newDistSq = (pos - m_enemys[i]->GetPosition()).LengthSq();
			if (newDistSq < bestDistSq) {
				bestDistSq = bestDistSq;
				best = m_enemys[i];
			}
		}
	}

	return best;
}







