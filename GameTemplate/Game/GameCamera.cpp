#include "stdafx.h"
#include "GameCamera.h"

#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");

	m_toPos = Vector3(0.0f,400.0f,250.0f);
	return true;
}

void GameCamera::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}

	Vector3 target = m_player->GetPosition();
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(target + m_toPos);

}