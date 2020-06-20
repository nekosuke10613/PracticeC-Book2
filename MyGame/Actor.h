#pragma once
#include<vector>
#include"Math.h"
#include<cstdint>
#include"SDL/SDL.h"

//�A�N�^�[�N���X 
//�ˑ����̒���(dependency injection)�p�^�[��
class Actor {
public :
	//�A�N�^�[�̏�ԊǗ��p
	enum State {
		EActive,
		EPaused,
		EDead,
	};
	Actor(class Game* game);
	virtual ~Actor();

	//�Q�[������Ă΂��X�V(override�s��)
	void Update(float deltaTime);
	//�R���|�[�l���g���X�V(override�s��)
	void UpdateComponents(float deltaTime);
	//�A�N�^�[�Ǝ��̍X�V����(override��)
	virtual void UpdateActor(float deltaTime);

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	/*  �Q�b�^�[/�Z�b�^�[   */
	//Pos
	const Vector2& GetPosition() const { return m_position; }
	void SetPosition(const Vector2& pos) {
		m_position = pos; }
	//Scale
	float GetScale()const { return m_scale; }
	void SetScale(float scale) { m_scale = scale; }
	//Rotation
	float GetRotation()const { return m_rotation; }
	void SetRotation(float rotation) { m_rotation = rotation; }
	
	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return m_worldTransform; }

	Vector2 GetForward() const { return Vector2(Math::Cos(m_rotation), -Math::Sin(m_rotation)); }

	//state
	State GetState()const { return m_state; }
	void SetState(State state) { m_state = state; }

	class Game* GetGame() { return m_game; }


	//�R���|�[�l���g�̒ǉ��E�폜
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* conponent);

private:
	//�A�N�^�[�̏��
	State m_state{ EActive };
	//���W�ϊ�
	Matrix4 m_worldTransform;
	Vector2 m_position{Vector2::Zero};
	float m_scale{ 1.0f };
	float m_rotation{ 0.0f };
	bool m_recomputeWorldTransform{ true };
	
	//�A�N�^�[�����R���|�[�l���g
	std::vector<class Component*> m_components;
	class Game* m_game;
};
