#include "stdafx.h"

SuperliminalObject::SuperliminalObject()
{
	LoadFile("testSphere.xml"); 
	state = SuperliminalObjectState::STAND;
	//gravity = 98.0f;// 중력가속도
	coef_res = 0.7f; // 완전 탄성 법칙 coefficient of restitution
	coef_friction = 0.99f; // friction (not phtsical) 마찰 계수

	// 정지 마찰력 운동 마찰력

}

void SuperliminalObject::UpdatePhysics()
{

	if (state == SuperliminalObjectState::STAND) {
		//velocity += gravity * DELTA;
		//velocity *= -UP*gravity;
		//MoveWorldPos(-UP * velocity * DELTA);
	}


	GameObject::Update();
}

void SuperliminalObject::ObjectHandleIN()
{
	state = SuperliminalObjectState::CHANGE;
}

void SuperliminalObject::ObjectHandleOUT()
{
	state = SuperliminalObjectState::STAND;
}

void SuperliminalObject::OnGround()
{

		//cout << velocity << endl;
		//cout << velocity << endl;

		state = SuperliminalObjectState::GROUND;
	
}

Vector3 SuperliminalObject::GetTransformWorldPos()
{
	return this->GetWorldPos();
}
