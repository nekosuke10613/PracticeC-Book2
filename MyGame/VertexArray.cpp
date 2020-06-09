#include "VertexArray.h"
#include<GL/glew.h>

VertexArray::VertexArray(const float * verts, unsigned int numVerts, const unsigned int * indices, unsigned int numIndices):
	m_numVerts(numVerts),
	m_numIndices(numIndices)
{
	//頂点配列の作成
	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	//頂点バッファの作成
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(
		GL_ARRAY_BUFFER,				//バッファの種類
		numVerts * 3 * sizeof(float),	//コピーするバイト数(頂点データ量×頂点の数(ｘｙｚ))
		verts,							//コピー元(ポインタ)
		GL_STATIC_DRAW	//(一回だけロード、頻繁にデータを読み込む)//このデータの利用方法
	);

	//インデックスバッファの作成
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,			//インデックスバッファの指定
		numIndices * sizeof(unsigned int),	//データのサイズ
		indices, GL_STATIC_DRAW);

	//頂点レイアウト(頂点属性)の指定
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,					//属性インデックス(1つ目はゼロ)
		3,					//要素数
		GL_FLOAT,			//要素の方
		GL_FALSE,			//(整数型のみ使用する)
		sizeof(float) * 5,	//ストライド(通常は各頂点のサイズ)
		0					//頂点データの開始位置からこの属性までのオフセット
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
