#pragma once
#include<vector>
#include"Math.h"
#include<cstdint>
#include"SDL/SDL.h"

//アクタークラス 
//依存性の注入(dependency injection)パターン
class Actor {
public :
	//アクターの状態管理用
	enum State {
		EActive,
		EPaused,
		EDead,
	};
	Actor(class Game* game);
	virtual ~Actor();

	//ゲームから呼ばれる更新(override不可)
	void Update(float deltaTime);
	//コンポーネントを更新(override不可)
	void UpdateComponents(float deltaTime);
	//アクター独自の更新処理(override可)
	virtual void UpdateActor(float deltaTime);

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	/*  ゲッター/セッター   */
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


	//コンポーネントの追加・削除
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* conponent);

private:
	//アクターの状態
	State m_state{ EActive };
	//座標変換
	Matrix4 m_worldTransform;
	Vector2 m_position{Vector2::Zero};
	float m_scale{ 1.0f };
	float m_rotation{ 0.0f };
	bool m_recomputeWorldTransform{ true };
	
	//アクターが持つコンポーネント
	std::vector<class Component*> m_components;
	class Game* m_game;
};
