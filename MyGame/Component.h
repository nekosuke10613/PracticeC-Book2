#pragma once

class Component {
public:
	//UpdateOrder���������R���|�[�l���g�قǑ����X�V�����
	Component(class Actor* owner, int updateOder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);

	int GetUpdateOrder()const { return m_updateOrder; }

protected:
	class Actor* m_owner;
	int m_updateOrder;

};
