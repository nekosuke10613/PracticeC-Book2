#pragma once

class VertexArray {
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	//���̒��_�z����A�N�e�B�u�ɂ���(�`��ł���悤�ɂ���)
	void SetActive();

	unsigned int GetNumIndices() const { return m_numIndices; }
	unsigned int GetNumVerts()const { return m_numVerts; }
private:
	//���_�o�b�t�@�ɂ��钸�_�̐�
	unsigned int m_numVerts;
	//�C���f�b�N�X�o�b�t�@�ɂ���C���f�b�N�X�̐�
	unsigned int m_numIndices;
	//���_�o�b�t�@��OpenGL�@ID
	unsigned int m_vertexBuffer;
	//�C���f�b�N�X�o�b�t�@��OpenGLID
	unsigned int m_indexBuffer;
	//���_�z��I�u�W�F�N�g��OpenGLID
	unsigned int m_vertexArray;
};