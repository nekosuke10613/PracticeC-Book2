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

	//キューの中身(未調査ノード)が空になるまで続ける
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
	//オープンセットの動的配列を定義
	std::vector<const WeightedGraphNode*> openSet;

	//現在のノードをStartに設定し、CloseSetにマーク
	const WeightedGraphNode* current = start;
	outMap[current].m_inClosedSet = true;

	do {
		//OpenSetに隣接ノードを追加する
		for (const WeightedEdge* edge : current->m_edges) {
			//このノードのスクラッチデータを取得する
			GBFSScratch& data = outMap[edge->m_to];
			//ClosedSetにない場合のみ追加する
			if (!data.m_inClosedSet) {
				//隣接ノードの親エッジを取得する
				data.m_parentEdge = edge;
				if (!data.m_inOpenSet) {
					//このノードのヒューリスティックを計算し、オープンセットに追加します
					data.m_heuristic = ComputeHeuristic(edge->m_to, goal);
					data.m_inOpenSet = true;
					openSet.emplace_back(edge->m_to);
				}

			}

		}
		//OpenSetが空なら使えるすべてのパスが使い果たされる
		if (openSet.empty()) {
			break;
		}
		//OpenSetから最もコストが低いノードを探す
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {
			return outMap[a].m_heuristic < outMap[b].m_heuristic;
		});
		//現在に設定しOpenからCloseに移動する
		current = *iter;
		openSet.erase(iter);
		outMap[current].m_inOpenSet = false;
		outMap[current].m_inClosedSet = true;
	} while (current != goal);

	//パスが見つかったか
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
	//オープンセットの動的配列を定義
	std::vector<const WeightedGraphNode*> openSet;

	//現在のノードをStartに設定し、CloseSetにマーク
	const WeightedGraphNode* current = start;
	outMap[current].m_inClosedSet = true;

	do {
		//OpenSetに隣接ノードを追加する
		for (const WeightedEdge* edge : current->m_edges) {
			const WeightedGraphNode* neighbor = edge->m_to;
			//このノードのスクラッチデータを取得
			Asterscratch& data = outMap[neighbor];
			//クローズドセットにないノードだけをチェック
			if (!data.m_inClosedSet) {
				if (!data.m_inOpenSet) {
					//オープンセットになければ親はカレントに違いない
					data.m_parentEdge = edge;
					data.m_heuristic = ComputeHeuristic(neighbor,goal);
					//実際のコストは、親のコスト＋エッジをたどるコスト
					data.m_actualFromStart = outMap[current].m_actualFromStart +
						edge->m_weight;
					data.m_inOpenSet = true;
					openSet.emplace_back(neighbor);

				}
				else {
					//選択中を親にしたときの経路コストを計算
					float newG = outMap[current].m_actualFromStart + edge->m_weight;
					if (newG < data.m_actualFromStart) {
						//このノードの親をカレントにする
						data.m_parentEdge = edge;
						data.m_actualFromStart = newG;
					}
				}
			}
		}
		//OpenSetが空なら使えるすべてのパスが使い果たされる
		if (openSet.empty()) {
			break;
		}
		//OpenSetから最もコストが低いノードを探す
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[&outMap](const WeightedGraphNode* a, const WeightedGraphNode* b) {
			//ノードa・bのf（x）を計算します
			float fOfA = outMap[a].m_heuristic + outMap[a].m_actualFromStart;
			float fOfB = outMap[b].m_heuristic + outMap[b].m_actualFromStart;
			return fOfA < fOfB;
		});
		//currentをセットして、Open→Closeに移動する
		current = *iter;
		openSet.erase(iter);
		outMap[current].m_inOpenSet = true;
		outMap[current].m_inClosedSet = true;
	} while (current != goal);

	//パスが見つかったか
	return (current == goal) ? true : false;

}
void TestHeuristic(bool useASter) {

}
