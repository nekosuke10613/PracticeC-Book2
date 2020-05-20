#include "Grid.h"
#include "Tile.h"
#include"Tower.h"
#include"Enemy.h"
#include<algorithm>

Grid::Grid(Game * game):
	Actor(game)
{
	//7�s16��
	m_tiles.resize(NUM_ROWS);
	for (size_t i = 0; i < m_tiles.size(); i++) {
		m_tiles[i].resize(NUM_COLS);
	}
	//�^�C���𐶐�����
	for (size_t i = 0; i < NUM_ROWS; i++) {
		for (size_t j = 0; j < NUM_COLS; j++) {
			m_tiles[i][j] = new Tile(GetGame());
			m_tiles[i][j]->SetPosition(
				Vector2(TILE_SIZE / 2.0f + j * TILE_SIZE, Start_Y + i * TILE_SIZE));
		}
	}
	//�n�_�ƏI�_�^�C����ݒ肷��
	GetStartTile()->SetTileState(Tile::EStart);
	GetEndTile()->SetTileState(Tile::EBase);

	//�אڃ��X�g�̐ݒ�
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
	//�p�X������(�t��)
	FindPath(GetEndTile(), GetStartTile());
	UpdatePathTiles(GetStartTile());

	m_nextEnemy = ENEMY_TIME;
}
void Grid::SelectTile(size_t row, size_t col)
{
	//�L���ȑI�����`�F�b�N
	Tile::TileState tState = m_tiles[row][col]->GetTileState();
	if (tState != Tile::EStart && tState != Tile::EBase) {
		//�O��̃^�C���I��������
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

//A* �̃p�X�T���@�\�̎���
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

	//���_��I�𒆃m�[�h�ɃZ�b�g���AClosedSet�ɂ��ǉ�����
	Tile* current = start;
	current->m_inClosedSet = true;

	do {
		//OpenSet�ɗאڃm�[�h��ǉ�����
		for (Tile* neighbor : current->m_adjacent) {
			if (neighbor->m_blooked)
				continue;
			//ClosedSet�ɂȂ��m�[�h�̂݃`�F�b�N����
			if (!neighbor->m_inClosedSet) {
				if (!neighbor->m_inOpenSet) {
					//OpenSet�ɂȂ���ΐe���Z�b�g����
					neighbor->m_parent = current;
					neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();
					// g�ix�j�͐e��g�ƃG�b�W���ړ�����R�X�g
					neighbor->g = current->g + TILE_SIZE;
					neighbor->f = neighbor->g + neighbor->h;
					openSet.emplace_back(neighbor);
					neighbor->m_inOpenSet = true;
				}
				else {
					//���I�𒆂̂��̂��e�Ȃ�Ag(x)�̃R�X�g���v�Z����
					float newG = current->g + TILE_SIZE;
					if (newG < neighbor->g) {
						//���̃m�[�h���̗p����
						neighbor->m_parent = current;
						neighbor->g = newG;
						// g�ix�j���ς�邽��f�ix�j���ς�� 
						neighbor->f = neighbor->g + neighbor->h;
					}
				}
			}
		}

		//�I�[�v���Z�b�g���󂾂����烋�[�v���甲����
		if (openSet.empty()) 
			break;
		//OpenSet���̍Œ�R�X�g�̃m�[�h��T��
		auto iter = std::min_element(openSet.begin(),openSet.end(),
			[](Tile* a, Tile* b) {
			return a->f < b->f;
		});
		//current�ɃZ�b�g����Open����Closed�Ɉړ�����
		current = *iter;
		openSet.erase(iter);
		current->m_inOpenSet = false;
		current->m_inClosedSet = true;
	} while (current != goal);

	return (current == goal) ? true : false;
}

void Grid::BuildTower()
{
	if (m_selectedTile && !m_selectedTile->m_blooked) {
		m_selectedTile->m_blooked = true;
		if (FindPath(GetEndTile(), GetStartTile())) {
			Tower* t = new Tower(GetGame());
			t->SetPosition(m_selectedTile->GetPosition());
		}
		else {

			//���̃^���[�̓p�X���u���b�N���邽�߁A���z�����Ȃ�
			m_selectedTile->m_blooked = false;
			FindPath(GetEndTile(), GetStartTile());
		}
		UpdatePathTiles(GetStartTile());
	}
}

Tile * Grid::GetStartTile()
{
	return m_tiles[3][0];
}

Tile * Grid::GetEndTile()
{
	return m_tiles[3][15];
}

void Grid::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	//��莞�Ԃ��ƂɐV�����G�𐶐�
	m_nextEnemy -= deltaTime;
	if (m_nextEnemy <= 0.0f) {
		new Enemy(GetGame());
		m_nextEnemy += ENEMY_TIME;
	}
}



void Grid::UpdatePathTiles(Tile * start)
{
	//�J�n�E�I���������ʏ�^�C�������Z�b�g����
	for (size_t i = 0; i < NUM_ROWS; i++) {
		for (size_t j = 0; j < NUM_COLS; j++) {
			if (!(i == 3 && j == 0) && !(i == 3 && j == 15))
				m_tiles[i][j]->SetTileState(Tile::EDefault);
		}
	}
	Tile* t = start->m_parent;
	while (t != GetEndTile()) {
		t->SetTileState(Tile::EPath);
		t = t->m_parent;
	}
}
