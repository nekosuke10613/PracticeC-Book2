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
		fileName.c_str(),	//ファイル名
		&m_width,			//幅
		&m_height,			//高さ
		&channnels,			//チャンネル数
		SOIL_LOAD_AUTO);	//画像ファイルの種類(またはauto)

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
		GL_TEXTURE_2D, //テクスチャターゲット
		0,		//LoD
		format,	//LOpenGLが使うべきカラーフォーマット
		m_width,//テクスチャの幅
		m_height,//テクスチャの高さ
		0,		//境界色(０)
		format,	//入力データのカラーフォーマット
		GL_UNSIGNED_BYTE,//入力データのビット震度
		image	//画像データへのポインタ
	);
	//SOILの画像データのメモリ開放
	SOIL_free_image_data(image);

	//バイリニアフィルタを有効にする
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
