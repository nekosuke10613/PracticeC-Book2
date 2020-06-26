#pragma once
#include<string>

class Texture {
public:
	Texture();
	~Texture();

	bool Load(const std::string& fileName);
	void Unload();

	void SetActive();

	int GetWidth()const { return m_width; }
	int GetHeight()const { return m_height; }
private:
	//このテクスチャのOpenGLID
	unsigned int m_textureId{ 0 };
	//テクスチャの幅と高さ
	int m_width{ 0 };
	int m_height{ 0 };
};
