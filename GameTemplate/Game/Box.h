#pragma once

class Box : public IGameObject
{

	Box();
	~Box();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	PhysicsStaticObject				m_physicsStaticObject;
	CollisionObject*				m_collisionObject;
	enum enBoxState
	{

	};
};

