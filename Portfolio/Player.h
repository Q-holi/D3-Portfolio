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

	float rotCamXAxisSpeed = 0.5f; // 카메라 x축 회전속도
	float rotCamYAxisSpeed = 0.3f; // 카메라 y축 회전속

	float limitMinX = -80.0f; // 카메라 x축 회전 범위 (최소)
	float limitMaxX = 50.0f; // 카메라 x축 회전 범위 (최대)

	float eulerAngleX; // 마우스 좌 / 우 이동으로 카메라 y축 회전
	float eulerAngleY; // 마우스 위 / 아래 이동으로 카메라 x축 회전
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

