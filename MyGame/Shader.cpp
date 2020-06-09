#include "Shader.h"
#include"Texture.h"
#include<SDL/SDL.h>
#include<fstream>
#include<sstream>

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::Load(const std::string & vertName, const std::string & fragName)
{
	//頂点シェーダーとフラグメントシェーダーをコンパイルする
	if (!CompleShader(vertName, GL_VERTEX_SHADER, m_vertexShader) ||
		!CompleShader(fragName, GL_FRAGMENT_SHADER, m_fragShader)) {
		return false;
	}
	//頂点・フラグメントシェーダーをリンクして
	//シェーダープログラムを作る
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragShader);
	glLinkProgram(m_shaderProgram);
	//プログラムが正しくリンクされたことを確認
	if (!IsValidProgram()) {
		return false;
	}
	return true;
}

void Shader::Unload()
{
	glDeleteProgram(m_shaderProgram);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragShader);
}

void Shader::SetActive()
{
	//シェーダープログラムをアクティブにする
	glUseProgram(m_shaderProgram);
}

void Shader::SetmatrixUniform(const char * name, const Matrix4 & matrix)
{
	GLuint loc = glGetUniformLocation(m_shaderProgram, name);
	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

bool Shader::CompleShader(const std::string & fileName, GLenum shaderType, GLuint & outShader)
{
	//ファイルを開く
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		//全てのテキストを1つの文字列に読み込む
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		//指定されたタイプのシェーダーを作成
		outShader = glCreateShader(shaderType);
		//読み込んだ文字列でのコンパイルを試みる
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader)) {
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else {
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}
	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	//コンパイル状態を問い合わせる
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	//エラーが発生している
	if (status != GL_TRUE) {
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;

	//リンク状態を問い合わせる
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(m_shaderProgram,511, nullptr, buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}

	return true;
}
