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


	float coef_res; // ���� ź�� ��Ģ coefficient of restitution
	float coef_friction ; // friction (not phtsical) ���� ���

public:
	SuperliminalObjectState	state;
	SuperliminalObject();
	void UpdatePhysics();
	void ObjectHandleIN();
	void ObjectHandleOUT();
	void OnGround();
	Vector3 GetTransformWorldPos();
};