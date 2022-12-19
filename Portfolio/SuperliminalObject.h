#pragma once
enum class SuperliminalObjectState
{
	STAND,
	CHANGE,
	GROUND
};


class SuperliminalObject : public Actor
{
private:


	float coef_res; // 완전 탄성 법칙 coefficient of restitution
	float coef_friction ; // friction (not phtsical) 마찰 계수

public:
	SuperliminalObjectState	state;
	SuperliminalObject();
	void UpdatePhysics();
	void ObjectHandleIN();
	void ObjectHandleOUT();
	void OnGround();
	Vector3 GetTransformWorldPos();
};