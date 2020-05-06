#pragma once


class AIState {
public:
	AIState(class AIComponent* owner):
		m_owner(owner){}
	//��Ԃ��Ƃ̂ӂ�܂�
	virtual void Update(float deltaTime) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	//��Ԗ��̎擾
	virtual const char* GetName() const = 0;
protected:
	class AIComponent* m_owner;
};
class AIPatrol : public AIState {
public:
	AIPatrol(class AIComponent* owner):
		AIState(owner){}

	void Update(float deltaTime)override;
	void OnEnter()override;
	void OnExit()override;

	const char* GetName()const override
	{
		return "Patrol";
	}
};
class AIDeath : public AIState {
public:
	AIDeath(class AIComponent* owner) :
		AIState(owner) {}

	void Update(float deltaTime)override;
	void OnEnter()override;
	void OnExit()override;

	const char* GetName()const override
	{
		return "Death";
	}
};
class AIAttack : public AIState {
public:
	AIAttack(class AIComponent* owner) :
		AIState(owner) {}

	void Update(float deltaTime)override;
	void OnEnter()override;
	void OnExit()override;

	const char* GetName()const override
	{
		return "Attack";
	}
};

