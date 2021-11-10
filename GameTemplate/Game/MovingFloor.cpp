#include "stdafx.h"
#include "MovingFloor.h"

#include "Player.h"

namespace
{
	Vector3	SCALE = Vector3(3.0f, 1.0, 3.0f);
	float SPEED = 200.0f;
	float LIMITED = 300.0f;
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 50.0f, 0.0f);
	Vector3	COLLISION_SIZE = Vector3(370.0f, 5.0f, 230.0f);
}

MovingFloor::MovingFloor()
{

}

MovingFloor::~MovingFloor()
{

}

bool MovingFloor::Start()
{
	m_modelRender.Init("Assets/modelData/sample/box.tkm");
	m_modelRender.SetScale(SCALE);
	//m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");

	//�R���W�����I�u�W�F�N�g���B
	//�������̏�ɐݒu����(�L�����N�^�[����ɏ�����甽������悤�ɂ���������)�B
	m_collisionObject->CreateBox(
		m_position + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_collisionObject->SetIsEnableAutoDelete(false);
	m_firstPosition = m_position;

	m_player = FindGO<Player>("player");
	return true;
}

void MovingFloor::Update()
{
	if (m_player == nullptr) 
	{
		m_player = FindGO<Player>("player");
		return;
	}


	Move();

	m_modelRender.Update();

	m_physicsStaticObject.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position + COLLISION_HEIGHT);
}

void MovingFloor::Move()
{

	Vector3 moveSpeed = Vector3::Zero;

	if (m_MovingFloorState == enMovingFloorState_MovingRight)
	{
		moveSpeed.x = -SPEED;
	}
	else if (m_MovingFloorState == enMovingFloorState_MovingLeft)
	{
		moveSpeed.x = SPEED;
	}

	m_position += moveSpeed * g_gameTime->GetFrameDeltaTime();

	if (m_MovingFloorState == enMovingFloorState_MovingRight)
	{
		if (m_firstPosition.x - LIMITED >= m_position.x)
		{
			m_MovingFloorState = enMovingFloorState_MovingLeft;
		}
	}
	else if (m_MovingFloorState == enMovingFloorState_MovingLeft)
	{
		if (m_firstPosition.x + LIMITED <= m_position.x)
		{
			m_MovingFloorState = enMovingFloorState_MovingRight;
		}
	}


	m_modelRender.SetPosition(m_position);

	//�R���W�����I�u�W�F�N�g�ƃv���C���[�̃L�����N�^�[�R���g���[���[���B
	//�Փ˂�����B(�L�����N�^�[���������̏�ɏ������)�B
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		//�������̈ړ����x���L�����N�^�[�̈ړ����x�ɉ��Z�B
		m_player->AddMoveSpeed(moveSpeed);
	}
}

void MovingFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}