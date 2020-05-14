#include "Grid.h"
#include "Tile.h"
#include<algorithm>

Grid::Grid(Game * game):
	Actor(game)
{
	//7行16列
	m_tiles.resize(NUM_ROWS);
	for (size_t i = 0; i < m_tiles.size(); i++) {
		m_tiles[i].resize(NUM_COLS);
	}
	//タイルを生成する
	for (size_t i = 0; i < NUM_ROWS; i++) {
		for (size_t j = 0; j < NUM_COLS; j++) {
			m_tiles[i][j] = new Tile(GetGame());
			m_tiles[i][j]->SetPosition(
				Vector2(TILE_SIZE / 2.0f + j * TILE_SIZE, Start_Y + i * TILE_SIZE));
		}
	}
	//始点と終点タイルを設定する
	GetStartTile()->SetTileState(Tile::EStart);
	GetEndTile()->SetTileState(Tile::EBase);

	//隣接リストの設定
	for (size_t i = 0; i < NUM_ROWS; i++) {
		for (size_t j = 0; j < NUM_COLS; j++) {
			if (i > 0) {
				m_tiles[i][j]->
					m_adjacent.push_back(m_tiles[i - 1][j]);
			}
			if (i < NUM_ROWS - 1) {
				m_tiles[i][j]->
					m_adjacent.push_back(m_tiles[i][j-1]);
			}
			if (j > 0) {
				m_tiles[i][j]->
					m_adjacent.push_back(m_tiles[i][j-1]);
			}
			if (j < NUM_COLS - 1) {
				m_tiles[i][j]->
					m_adjacent.push_back(m_tiles[i][j+1]);
			}

		}
	}
	//パスを検索(逆順)
	FindPath(GetEndTile(), GetStartTile());
	UpdatePathTiles(GetStartTile());

	m_nextEnemy = ENEMY_TIME;
}
void Grid::SelectTile(size_t row, size_t col)
{
	//有効な選択かチェック
	Tile::TileState tState = m_tiles[row][col]->GetTileState();
	if (tState != Tile::EStart && tState != Tile::EBase) {
		//前回のタイル選択を解除
		if (m_selectedTile) {
			m_selectedTile->ToggleSelect();
		}
		m_selectedTile = m_tiles[row][col];
		m_selectedTile->ToggleSelect();
	}
}

void Grid::ProcessClick(int x, int y)
{
	y -= static_cast<int>(Start_Y - TILE_SIZE / 2);
	if (y >= 0) {
		x /= static_cast<int>(TILE_SIZE);
		y /= static_cast<int>(TILE_SIZE);
		if (x >= 0 && x < static_cast<int>(NUM_COLS)
			&& x >= 0 && y < static_cast<int>(NUM_ROWS)) {
			SelectTile(y, x);
		}
	}
}

//A* のパス探索機能の実装
bool Grid::FindPath(Tile * start, Tile * goal)
{
	for (size_t i = 0; i < NUM_ROWS; i++ ) {
		for (size_t j = 0; j < NUM_COLS; j++) {
			m_tiles[i][j]->g = 0.0f;
			m_tiles[i][j]->m_inOpenSet = false;
			m_tiles[i][j]->m_inClosedSet = false;
		}
	}
	std::vector<Tile*> openSet;

	//視点を選択中ノードにセットし、ClosedSetにも追加する
	Tile* current = start;
	current->m_inClosedSet = true;

	do {
		//OpenSetに隣接ノードを追加する
		for (Tile* neighbor : current->m_adjacent) {
			if (neighbor->m_blooked)
				continue;
			//ClosedSetにないノードのみチェックする
			if (!neighbor->m_inClosedSet) {
				if (!neighbor->m_inOpenSet) {
					//OpenSetになければ親をセットする
					neighbor->m_parent = current;
					neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();
					// g（x）は親のgとエッジを移動するコスト
					neighbor->g = current->g + TILE_SIZE;
					neighbor->f = neighbor->g + neighbor->h;
					openSet.emplace_back(neighbor);
					neighbor->m_inOpenSet = true;
				}
				else {
					//今選択中のものが親なら、g(x)のコストを計算する
				}
			}
		}
	}
	return false;
}

void Grid::BuildTower()
{
}

Tile * Grid::GetStartTile()
{
	return nullptr;
}

Tile * Grid::GetEndTile()
{
	return nullptr;
}

void Grid::UpdateActor(float deltaTime)
{
}



void Grid::UpdatePathTiles(Tile * start)
{
}
