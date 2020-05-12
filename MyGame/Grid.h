#pragma once
#include"Actor.h"
#include<vector>

class Grid : public Actor {
public:
	Grid(class Game* game);

	//�X�N���[�����W�����̏ꏊ�ŃN���b�N�������s��
	void ProcessClick(int x, int y);

	//A*�ւ̃p�X��T���Ďg��
	bool FindPath(class Tile* start, class Tile* goal);

	//�^���[�̌��z������
	void BuildTower();

	//�X�^�[�g�n�_�E�S�[���n�_�̃^�C�����擾����
	class Tile* GetStartTile();
	class Tile* GetEndTile();

	void UpdateActor(float deltaTime)override;
private:
	//����̃^�C����I������
	void SelectTile(size_t rox, size_t col);

	//�p�X��̃^�C���̃e�N�X�`�����X�V����
	void UpdatePathTiles(class Tile* start);

private:

	//�I�𒆂̃^�C��
	class Tile* m_selectedTile{ nullptr };

	std::vector<std::vector<class Tile*>> m_tiles;

	//���̓G�܂ł̎���
	float m_nextEnemy;

	//�O���b�h�̍s/��
	const size_t NUM_ROWS = 7;
	const size_t NUM_COLS = 16;
	//�X�^�[�g�n�_�̍�����Y���W
	const float Start_Y = 192.0f;
	//�^�C���̏c������
	const float TILE_SIZE = 64.0f;
	//Enemy�Ԃ̎���
	const float ENEMY_TIME = 1.5f;
};
