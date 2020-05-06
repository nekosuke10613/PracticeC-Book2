#pragma once
#include<vector>
#include<queue>
#include<iostream>
#include<unordered_map>

struct GraphNode {
	//各ノードは隣接ノードへのポインタを持つ
	std::vector<GraphNode*> m_adjacent;
};
struct Graph {
	//グラフはノードを含む
	std::vector<GraphNode*> m_nodes;
};
struct WeightedEdge {
	//エッジにつながってるノード
	struct WeightedGraphNode* m_from;
	struct WeightedGraphNode* m_to;
	//エッジの重み
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
	//経路を見つけたか？
	bool pathFound = false;
	//検討するノード
	std::queue<const GraphNode*> q;
	//最初のノードをキューに入れる
	q.emplace(start);

	while (!q.empty()) {
		//ノードを1つキューから出す
		const GraphNode* current = q.front();
		q.pop();
		if (current == goal) {
			pathFound = true;
			break;
		}
		//まだキューに入ってない隣接ノードをエンキューする
		for (const GraphNode* node : current->m_adjacent) {
			//もし親がnullptrなら、まだキューに追加されていない
			//(ただし開始ノードは例外)
			const GraphNode* parent = outMap[node];
			if (parent == nullptr && node != start) {
				//このノードのエンキューと親の設定をする
				outMap[node] = current;
				q.emplace(node);
			}
		}
	}
	return pathFound;
}
void TestBFS() {
	//上の(幅優先探索)使い方例
	Graph g;
	//まずグラフノードをいっぱい作ります
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			GraphNode* node = new GraphNode;
			g.m_nodes.emplace_back(node);
		}
	}
	//次に隣接の情報を追加していきます
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
		// 1 - 2 - 3 - 4  みたいなイメージ？
		//   ＼　　／
		//　　　 5
		//探します
		NodeToParentMap map;
		bool found = BFS(g, g.m_nodes[0], g.m_nodes[9], map);
		std::cout << found << '\n';
	}
	

}