#include "stdafx.h"

SuperliminalObject::SuperliminalObject()
{
	LoadFile("testSphere.xml"); 
	state = SuperliminalObjectState::STAND;
	//gravity = 98.0f;// �߷°��ӵ�
	coef_res = 0.7f; // ���� ź�� ��Ģ coefficient of restitution
	coef_friction = 0.99f; // friction (not phtsical) ���� ���

	// ���� ������ � ������

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
