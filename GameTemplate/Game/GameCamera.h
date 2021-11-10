#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start() override;
	void Update() override;
private:
	Player* m_player = nullptr;
	Vector3	m_toPos;
};

