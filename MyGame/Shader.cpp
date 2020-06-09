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
	//���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[���R���p�C������
	if (!CompleShader(vertName, GL_VERTEX_SHADER, m_vertexShader) ||
		!CompleShader(fragName, GL_FRAGMENT_SHADER, m_fragShader)) {
		return false;
	}
	//���_�E�t���O�����g�V�F�[�_�[�������N����
	//�V�F�[�_�[�v���O���������
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, m_vertexShader);
	glAttachShader(m_shaderProgram, m_fragShader);
	glLinkProgram(m_shaderProgram);
	//�v���O�����������������N���ꂽ���Ƃ��m�F
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
	//�V�F�[�_�[�v���O�������A�N�e�B�u�ɂ���
	glUseProgram(m_shaderProgram);
}

void Shader::SetmatrixUniform(const char * name, const Matrix4 & matrix)
{
	GLuint loc = glGetUniformLocation(m_shaderProgram, name);
	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

bool Shader::CompleShader(const std::string & fileName, GLenum shaderType, GLuint & outShader)
{
	//�t�@�C�����J��
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		//�S�Ẵe�L�X�g��1�̕�����ɓǂݍ���
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		//�w�肳�ꂽ�^�C�v�̃V�F�[�_�[���쐬
		outShader = glCreateShader(shaderType);
		//�ǂݍ��񂾕�����ł̃R���p�C�������݂�
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
	//�R���p�C����Ԃ�₢���킹��
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	//�G���[���������Ă���
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

	//�����N��Ԃ�₢���킹��
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
