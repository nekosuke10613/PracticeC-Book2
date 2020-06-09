#pragma once
#include<GL/glew.h>
#include<string>
#include"Math.h"

class Shader {
public:
	Shader();
	~Shader();
	//指定された名前の頂点・ピクセルシェーダーを読みこむ
	bool Load(const std::string& vertName, const std::string& gragName);
	void Unload();
	//アクティブなシェーダープログラムとして設定
	void SetActive();
	//MatrixUniformを設定
	void SetmatrixUniform(const char* name, const Matrix4& matrix);

private:
	//シェーダーをコンパイルする
	bool CompleShader(const std::string& fileName,
					  GLenum shaderType,
					  GLuint& outShader);
	//シェーダーのコンパイルに成功したか
	bool IsCompiled(GLuint shader);
	//頂点・フラグメントプログラムのリンクを確認
	bool IsValidProgram();
private:
	//シェーダーオブジェクトのIDを格納
	GLuint m_vertexShader{ 0 };
	GLuint m_fragShader{ 0 };
	GLuint m_shaderProgram{ 0 };

};
