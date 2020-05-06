#pragma once
#include<vector>
#include<queue>
#include<iostream>
#include<unordered_map>

struct GraphNode {
	//�e�m�[�h�͗אڃm�[�h�ւ̃|�C���^������
	std::vector<GraphNode*> m_adjacent;
};
struct Graph {
	//�O���t�̓m�[�h���܂�
	std::vector<GraphNode*> m_nodes;
};
struct WeightedEdge {
	//�G�b�W�ɂȂ����Ă�m�[�h
	struct WeightedGraphNode* m_from;
	struct WeightedGraphNode* m_to;
	//�G�b�W�̏d��
	float m_weight;
};
struct WeightedGraphNode {
	std::vector<WeightedEdge*> m_edges;
};
struct WeightedGraph {
	std::vector<WeightedGraphNode*> m_nodes;
};

using NodeToParentMap = std::unordered_map<const GraphNode*, const GraphNode*>;

bool BFS(const Graph& graph, const GraphNode* start,
	const GraphNode* goal, NodeToParentMap& outMap) {
	//�o�H�����������H
	bool pathFound = false;
	//��������m�[�h
	std::queue<const GraphNode*> q;
	//�ŏ��̃m�[�h���L���[�ɓ����
	q.emplace(start);

	while (!q.empty()) {
		//�m�[�h��1�L���[����o��
		const GraphNode* current = q.front();
		q.pop();
		if (current == goal) {
			pathFound = true;
			break;
		}
		//�܂��L���[�ɓ����ĂȂ��אڃm�[�h���G���L���[����
		for (const GraphNode* node : current->m_adjacent) {
			//�����e��nullptr�Ȃ�A�܂��L���[�ɒǉ�����Ă��Ȃ�
			//(�������J�n�m�[�h�͗�O)
			const GraphNode* parent = outMap[node];
			if (parent == nullptr && node != start) {
				//���̃m�[�h�̃G���L���[�Ɛe�̐ݒ������
				outMap[node] = current;
				q.emplace(node);
			}
		}
	}
	return pathFound;
}
void TestBFS() {
	//���(���D��T��)�g������
	Graph g;
	//�܂��O���t�m�[�h�������ς����܂�
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			GraphNode* node = new GraphNode;
			g.m_nodes.emplace_back(node);
		}
	}
	//���ɗאڂ̏���ǉ����Ă����܂�
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			GraphNode* node = g.m_nodes[i * 5 + j];
			if (i > 0)
			{
				node->m_adjacent.emplace_back(g.m_nodes[(i - 1) * 5 + j]);
			}
			if (i < 4)
			{
				node->m_adjacent.emplace_back(g.m_nodes[(i + 1) * 5 + j]);
			}
			if (j > 0)
			{
				node->m_adjacent.emplace_back(g.m_nodes[i * 5 + j - 1]);
			}
			if (j < 4)
			{
				node->m_adjacent.emplace_back(g.m_nodes[i * 5 + j + 1]);
			}
		}
		// 1 - 2 - 3 - 4  �݂����ȃC���[�W�H
		//   �_�@�@�^
		//�@�@�@ 5
		//�T���܂�
		NodeToParentMap map;
		bool found = BFS(g, g.m_nodes[0], g.m_nodes[9], map);
		std::cout << found << '\n';
	}
	

}