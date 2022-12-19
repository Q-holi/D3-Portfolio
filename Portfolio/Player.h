#pragma once

enum class PlayerState
{
	IDLE,
	WALK
};
class Player : public Actor
{
private:
	PlayerState state;
	//float		gravity;
	Vector3     lastPos;

	
	bool moveCamera = false;

private:
	void Idle();
	void Walk();

public:

	float rotCamXAxisSpeed = 0.5f; // ī�޶� x�� ȸ���ӵ�
	float rotCamYAxisSpeed = 0.3f; // ī�޶� y�� ȸ����

	float limitMinX = -80.0f; // ī�޶� x�� ȸ�� ���� (�ּ�)
	float limitMaxX = 50.0f; // ī�޶� x�� ȸ�� ���� (�ִ�)

	float eulerAngleX; // ���콺 �� / �� �̵����� ī�޶� y�� ȸ��
	float eulerAngleY; // ���콺 �� / �Ʒ� �̵����� ī�޶� x�� ȸ��
	bool		jumping;
	Player();
	//static Player* Create(string name = "Player");
	void Update();
	void WorldUpdate();
	void ClampAngle(float angle, float min, float max);
	bool GetJumpping() { return jumping; }
	Vector3 GetLastPos() { return lastPos; }
	void Falling();
	void Landing();
};

