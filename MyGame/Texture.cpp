#include "Texture.h"
#include<SOIL/SOIL.h>
#include<GL/glew.h>
#include<SDL/SDL.h>

Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::Load(const std::string & fileName)
{
	int channnels = 0;

	unsigned char* image = SOIL_load_image(
		fileName.c_str(),	//�t�@�C����
		&m_width,			//��
		&m_height,			//����
		&channnels,			//�`�����l����
		SOIL_LOAD_AUTO);	//�摜�t�@�C���̎��(�܂���auto)

	if (image == nullptr) {
		SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}

	int format = GL_RGB;
	if (channnels == 4) {
		format = GL_RGBA;
	}

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	glTexImage2D(
		GL_TEXTURE_2D, //�e�N�X�`���^�[�Q�b�g
		0,		//LoD
		format,	//LOpenGL���g���ׂ��J���[�t�H�[�}�b�g
		m_width,//�e�N�X�`���̕�
		m_height,//�e�N�X�`���̍���
		0,		//���E�F(�O)
		format,	//���̓f�[�^�̃J���[�t�H�[�}�b�g
		GL_UNSIGNED_BYTE,//���̓f�[�^�̃r�b�g�k�x
		image	//�摜�f�[�^�ւ̃|�C���^
	);
	//SOIL�̉摜�f�[�^�̃������J��
	SOIL_free_image_data(image);

	//�o�C���j�A�t�B���^��L���ɂ���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &m_textureId);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}
