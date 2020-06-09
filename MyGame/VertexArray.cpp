#include "VertexArray.h"
#include<GL/glew.h>

VertexArray::VertexArray(const float * verts, unsigned int numVerts, const unsigned int * indices, unsigned int numIndices):
	m_numVerts(numVerts),
	m_numIndices(numIndices)
{
	//���_�z��̍쐬
	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	//���_�o�b�t�@�̍쐬
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(
		GL_ARRAY_BUFFER,				//�o�b�t�@�̎��
		numVerts * 3 * sizeof(float),	//�R�s�[����o�C�g��(���_�f�[�^�ʁ~���_�̐�(������))
		verts,							//�R�s�[��(�|�C���^)
		GL_STATIC_DRAW	//(��񂾂����[�h�A�p�ɂɃf�[�^��ǂݍ���)//���̃f�[�^�̗��p���@
	);

	//�C���f�b�N�X�o�b�t�@�̍쐬
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,			//�C���f�b�N�X�o�b�t�@�̎w��
		numIndices * sizeof(unsigned int),	//�f�[�^�̃T�C�Y
		indices, GL_STATIC_DRAW);

	//���_���C�A�E�g(���_����)�̎w��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,					//�����C���f�b�N�X(1�ڂ̓[��)
		3,					//�v�f��
		GL_FLOAT,			//�v�f�̕�
		GL_FALSE,			//(�����^�̂ݎg�p����)
		sizeof(float) * 5,	//�X�g���C�h(�ʏ�͊e���_�̃T�C�Y)
		0					//���_�f�[�^�̊J�n�ʒu���炱�̑����܂ł̃I�t�Z�b�g
	);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3,
		reinterpret_cast<void*>(sizeof(float) * 3));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1,&m_indexBuffer);
	glDeleteVertexArrays(1, &m_vertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(m_vertexArray);
}
