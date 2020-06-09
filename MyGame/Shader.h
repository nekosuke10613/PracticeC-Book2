#pragma once
#include<GL/glew.h>
#include<string>
#include"Math.h"

class Shader {
public:
	Shader();
	~Shader();
	//�w�肳�ꂽ���O�̒��_�E�s�N�Z���V�F�[�_�[��ǂ݂���
	bool Load(const std::string& vertName, const std::string& gragName);
	void Unload();
	//�A�N�e�B�u�ȃV�F�[�_�[�v���O�����Ƃ��Đݒ�
	void SetActive();
	//MatrixUniform��ݒ�
	void SetmatrixUniform(const char* name, const Matrix4& matrix);

private:
	//�V�F�[�_�[���R���p�C������
	bool CompleShader(const std::string& fileName,
					  GLenum shaderType,
					  GLuint& outShader);
	//�V�F�[�_�[�̃R���p�C���ɐ���������
	bool IsCompiled(GLuint shader);
	//���_�E�t���O�����g�v���O�����̃����N���m�F
	bool IsValidProgram();
private:
	//�V�F�[�_�[�I�u�W�F�N�g��ID���i�[
	GLuint m_vertexShader{ 0 };
	GLuint m_fragShader{ 0 };
	GLuint m_shaderProgram{ 0 };

};
