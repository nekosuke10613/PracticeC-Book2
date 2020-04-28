#include"Game.h"
#include"SDL/SDL_image.h"
#include<algorithm>
#include"Actor.h"
#include"SpriteComponent.h"
#include"Ship.h"
#include "BGSpriteComponent.h"


Game::Game() :
	m_window(nullptr),
	m_renderer(nullptr),
	m_isRunning(true),
	m_updatetingActors(false)
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
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		SDL_Log("SDL_Image�̍쐬�Ɏ��s���܂���:%s", SDL_GetError());
		return false;
	}
	LoadData();

	m_ticksCount = SDL_GetTicks();
	

	//�����܂ŗ����琬��
	return true;
}
void Game::LoadData()
{
	m_ship = new Ship(this);
	m_ship->SetPosition(Vector2(100.0f, 384.0f));
	m_ship->SetScale(1.5f);

	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));

	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTexture(bgtexs);
	bg->SetScrollSpeed(-100.0f);

	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bg->SetBGTexture(bgtexs);
	bg->SetScrollSpeed(-200.0f);
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
	UnloadData();
	IMG_Quit();
	//Window��j������
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
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
		tex = SDL_CreateTextureFromSurface(m_renderer, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("surface�̃e�N�X�`���ϊ��Ɏ��s���܂��� �t�@�C����:%s", fileName.c_str());
			return nullptr;
		}

		m_texture.emplace(fileName.c_str(), tex);
	}
	return tex;
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
	m_ship->ProceessKeyboard(state);
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
		if (actor->GetScale() == Actor::EDead) {
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
	// Draw all sprite components
	for (auto sprite : m_sprite)
	{
		sprite->Draw(m_renderer);
	}
	

	//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@������
	SDL_RenderPresent(m_renderer);
}


