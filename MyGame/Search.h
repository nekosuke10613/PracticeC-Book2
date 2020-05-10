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

	//�L���[�̒��g(�������m�[�h)����ɂȂ�܂ő�����
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
float ComputeHeuristic(const WeightedGraphNode*, const WeightedGraphNode* b) {
	return 0.0f;
}
struct GBFSScratch {
	const WeightedEdge* m_parentEdge = nullptr;
	float m_heuristic = 0.0f;
	bool m_inOpenSet = false;
	bool m_inClosedSet = false;
};
using GBFSMap =
std::unordered_map<const WeightedGraphNode*, GBFSScratch>;

bool GBFS(const WeightedGraph& g, const WeightedGraphNode* start,
	const WeightedGraphNode* goal, GBFSMap& outMap) {
	//�I�[�v���Z�b�g�̓��I�z����`
	std::vector<const WeightedGraphNode*> openSet;

	//���݂̃m�[�h��Start�ɐݒ肵�ACloseSet�Ƀ}�[�N
	const WeightedGraphNode* current = start;
	outMap[current].m_inClosedSet = true;

	do {
		//OpenSet�ɗאڃm�[�h��ǉ�����
		for (const WeightedEdge* edge : current->m_edges) {
			//���̃m�[�h�̃X�N���b�`�f�[�^���擾����
			GBFSScratch& data = outMap[edge->m_to];
			//ClosedSet�ɂȂ��ꍇ�̂ݒǉ�����
			if (!data.m_inClosedSet) {
				//�אڃm�[�h�̐e�G�b�W���擾����
				data.m_parentEdge = edge;
				if (!data.m_inOpenSet) {
					//���̃m�[�h�̃q���[���X�e�B�b�N���v�Z���A�I�[�v���Z�b�g�ɒǉ����܂�
					data.m_heuristic = ComputeHeuristic(edge->m_to, goal);
					data.m_inOpenSet = true;
					openSet.emplace_back(edge->m_to);
				}

			}

		}
		//OpenSet����Ȃ�g���邷�ׂẴp�X���g���ʂ������
		if (openSet.empty()) {
			break;
		}
		//OpenSet����ł��R�X�g���Ⴂ�m�[�h��T��
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {
			return outMap[a].m_heuristic < outMap[b].m_heuristic;
		});
		//���݂ɐݒ肵Open����Close�Ɉړ�����
		current = *iter;
		openSet.erase(iter);
		outMap[current].m_inOpenSet = false;
		outMap[current].m_inClosedSet = true;
	} while (current != goal);

	//�p�X������������
	return (current == goal) ? true : false;
}

struct Asterscratch {
	const WeightedEdge* m_parentEdge = nullptr;
	float m_heuristic = 0.0f;
	float m_actualFromStart = 0.0f;
	bool m_inOpenSet = false;
	bool m_inClosedSet = false;
};
using AStarMap =
std::unordered_map<const WeightedGraphNode*, Asterscratch>;

bool Aster(const WeightedGraph& g, const WeightedGraphNode* start,
	const WeightedGraphNode* goal, AStarMap&  outMap) {
	//�I�[�v���Z�b�g�̓��I�z����`
	std::vector<const WeightedGraphNode*> openSet;

	//���݂̃m�[�h��Start�ɐݒ肵�ACloseSet�Ƀ}�[�N
	const WeightedGraphNode* current = start;
	outMap[current].m_inClosedSet = true;

	do {
		//OpenSet�ɗאڃm�[�h��ǉ�����
		for (const WeightedEdge* edge : current->m_edges) {
			const WeightedGraphNode* neighbor = edge->m_to;
			//���̃m�[�h�̃X�N���b�`�f�[�^���擾
			Asterscratch& data = outMap[neighbor];
			//�N���[�Y�h�Z�b�g�ɂȂ��m�[�h�������`�F�b�N
			if (!data.m_inClosedSet) {
				if (!data.m_inOpenSet) {
					//�I�[�v���Z�b�g�ɂȂ���ΐe�̓J�����g�ɈႢ�Ȃ�
					data.m_parentEdge = edge;
					data.m_heuristic = ComputeHeuristic(neighbor,goal);
					//���ۂ̃R�X�g�́A�e�̃R�X�g�{�G�b�W�����ǂ�R�X�g
					data.m_actualFromStart = outMap[current].m_actualFromStart +
						edge->m_weight;
					data.m_inOpenSet = true;
					openSet.emplace_back(neighbor);

				}
				else {
					//�I�𒆂�e�ɂ����Ƃ��̌o�H�R�X�g���v�Z
					float newG = outMap[current].m_actualFromStart + edge->m_weight;
					if (newG < data.m_actualFromStart) {
						//���̃m�[�h�̐e���J�����g�ɂ���
						data.m_parentEdge = edge;
						data.m_actualFromStart = newG;
					}
				}
			}
		}
		//OpenSet����Ȃ�g���邷�ׂẴp�X���g���ʂ������
		if (openSet.empty()) {
			break;
		}
		//OpenSet����ł��R�X�g���Ⴂ�m�[�h��T��
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {
			//�m�[�ha�Eb��f�ix�j���v�Z���܂�
			float fOfA = outMap[a].m_heuristic + outMap[a].m_actualFromStart;
			float fOfB = outMap[b].m_heuristic + outMap[b].m_actualFromStart;
			return fOfA < fOfB;
		});
		//current���Z�b�g���āAOpen��Close�Ɉړ�����
		current = *iter;
		openSet.erase(iter);
		outMap[current].m_inOpenSet = true;
		outMap[current].m_inClosedSet = true;
	} while (current != goal);

	//�p�X������������
	return (current == goal) ? true : false;

}
void TestHeuristic(bool useASter) {

}
