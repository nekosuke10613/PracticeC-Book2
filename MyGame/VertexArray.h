#pragma once

class VertexArray {
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	//この頂点配列をアクティブにする(描画できるようにする)
	void SetActive();

	unsigned int GetNumIndices() const { return m_numIndices; }
	unsigned int GetNumVerts()const { return m_numVerts; }
private:
	//頂点バッファにある頂点の数
	unsigned int m_numVerts;
	//インデックスバッファにあるインデックスの数
	unsigned int m_numIndices;
	//頂点バッファのOpenGL　ID
	unsigned int m_vertexBuffer;
	//インデックスバッファのOpenGLID
	unsigned int m_indexBuffer;
	//頂点配列オブジェクトのOpenGLID
	unsigned int m_vertexArray;
};