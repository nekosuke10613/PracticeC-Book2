#pragma once
#include"Actor.h"
#include<vector>

class Grid : public Actor {
public:
	Grid(class Game* game);

	//スクリーン座標ｘｙの場所でクリック処理を行う
	void ProcessClick(int x, int y);

	//A*へのパスを探して使う
	bool FindPath(class Tile* start, class Tile* goal);

	//タワーの建築をする
	void BuildTower();

	//スタート地点・ゴール地点のタイルを取得する
	class Tile* GetStartTile();
	class Tile* GetEndTile();

	void UpdateActor(float deltaTime)override;
private:
	//特定のタイルを選択する
	void SelectTile(size_t rox, size_t col);

	//パス上のタイルのテクスチャを更新する
	void UpdatePathTiles(class Tile* start);

private:

	//選択中のタイル
	class Tile* m_selectedTile{ nullptr };

	std::vector<std::vector<class Tile*>> m_tiles;

	//次の敵までの時間
	float m_nextEnemy;

	//グリッドの行/列
	const size_t NUM_ROWS = 7;
	const size_t NUM_COLS = 16;
	//スタート地点の左隅のY座標
	const float Start_Y = 192.0f;
	//タイルの縦横長さ
	const float TILE_SIZE = 64.0f;
	//Enemy間の時間
	const float ENEMY_TIME = 1.5f;
};
