#include "stdafx.h"


//Player* Player::Create(string name)
//{
//	Player* temp = new Player();
//	return temp;
//}

Player::Player()
{
	LoadFile("User.xml");
	state = PlayerState::IDLE;
	jumping = false;

	limitMinX = -80.0f; // ī�޶� x�� ȸ�� ���� (�ּ�)
	limitMaxX = 50.0f; // ī�޶� x�� ȸ�� ���� (�ִ�)d
}

void Player::Update()
{
	//�����̱� ���� ��ġ��
	lastPos = GetWorldPos();


	switch (state)
	{
	case PlayerState::IDLE:
		Idle();
		break;
	case PlayerState::WALK:
		Walk();
		break;
	}
	if (INPUT->KeyPress('A'))
	{
		position += -GetRight() * 75.0f * DELTA;
		//rotation.y -= DELTA;
	}
	if (INPUT->KeyPress('D'))
	{
		position += GetRight() * 75.0f * DELTA;
		//rotation.y += DELTA;
	}
	if (INPUT->KeyDown(VK_SPACE) and not jumping)
	{
		jumping = true;
		//gravity = -30.0f;
	}

	if (jumping)
	{
		//MoveWorldPos(-UP * gravity * DELTA);
		//gravity += 30.0f * DELTA;
		/*if (gravity > 30.0f)
		{
			jumping = false;
		}*/
	}


	Actor::Update();
}

void Player::WorldUpdate()
{
	Transform::Update();
}

void Player::Falling()
{
	if (jumping) return;
	jumping = true;
	//gravity = 0.0f;
}

void Player::Landing()
{
	if (not jumping) return;
	jumping = false;
	//gravity = 0.0f;
}

void Player::Idle()
{
	//������,�����ڼ�����
	//Find("Head")->rotation.y += mul * DELTA;

	//idle to walk
	if (INPUT->KeyPress('W') or INPUT->KeyPress('S'))
	{
		state = PlayerState::WALK;
		anim->PlayAnimation(AnimationState::LOOP, 0);
	}
}

void Player::Walk()
{
	if (INPUT->KeyPress('W'))
	{
		position += GetForward() * 75.0f * DELTA;
	}
	if (INPUT->KeyPress('S'))
	{
		position -= GetForward() * 75.0f * DELTA;
	}
	//�ȴٸ�������,������
	//Find("Head")->rotation.y = 0.0f;

	//walk to idle
	if (INPUT->KeyPress('W') == false and INPUT->KeyPress('S') == false)
	{
		state = PlayerState::IDLE;
		anim->PlayAnimation(AnimationState::STOP, 0);
	}
}

void Player::ClampAngle(float angle, float min, float max)
{

	if (angle < -360)
	{
		angle += 360;
	}

	if (angle > 360)
	{
		angle -= 360;
	}

	//return Util::Saturate(angle, min, max);
	//return Mathf.Clamp(angle, min, max);
}
