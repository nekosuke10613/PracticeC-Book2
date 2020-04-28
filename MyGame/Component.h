#pragma once

class Component {
public:
	//UpdateOrderが小さいコンポーネントほど早く更新される
	Component(class Actor* owner, int updateOder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);

	int GetUpdateOrder()const { return m_updateOrder; }

protected:
	class Actor* m_owner;
	int m_updateOrder;

};
