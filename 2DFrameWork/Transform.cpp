#include "framework.h"
bool Transform::worldPos = false;
ID3D11Buffer* Transform::WBuffer = nullptr;
void Transform::CreateStaticMember()
{
	D3D11_BUFFER_DESC desc = { 0 };
	desc.ByteWidth = sizeof(Matrix);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &WBuffer);
	assert(SUCCEEDED(hr));

	D3D->GetDC()->VSSetConstantBuffers(0, 1, &WBuffer);
}
void Transform::DeleteStaticMember()
{
	SafeRelease(WBuffer);
}

void Transform::Set()
{
	Matrix TW = W.Transpose();
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	D3D->GetDC()->Map(WBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy_s(mappedResource.pData, sizeof(Matrix), &TW, sizeof(Matrix));
	D3D->GetDC()->Unmap(WBuffer, 0);
}

Transform::Transform()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	scale.x = 1.0f;
	scale.y = 1.0f;
	scale.z = 1.0f;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;
	parent = nullptr;

	//*****************물리엔진에 필요한 각 변수들 **********************
	linearDamping = 0.99f;
	angularDamping = 0.99f;
}

void Transform::Update()
{
	S = Matrix::CreateScale(scale.x, scale.y, scale.z);
	// Ry*Rx*Rz
	R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	T = Matrix::CreateTranslation(position.x, position.y, position.z);
	RT = R * T;
	W = S * RT;
	if (parent)
	{
		S *= parent->S;
		RT *= parent->RT;
		W *= parent->W;
	}
}

void Transform::UpdateAnim(Matrix&& bone)
{
	S = Matrix::CreateScale(scale);
	R = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	T = Matrix::CreateTranslation(position);

	RT = R * T * bone;
	W = S * RT;
	if (parent)
	{
		S = S * parent->S;
		RT = RT * parent->RT;
		W = W * parent->W;
	}
}


Vector3 Transform::GetWorldPos()
{
	return Vector3(W._41, W._42, W._43);
}

void Transform::SetWorldPos(Vector3 WPos)
{
	if (parent)
		position = Vector3::Transform(WPos, parent->W.Invert());
	else
		position = WPos;
}

void Transform::SetWorldPosX(float WPosX)
{
	if (parent)
		position.x = Vector3::Transform(Vector3(WPosX, W._42, W._43), parent->W.Invert()).x;
	else
		position.x = WPosX;
}

void Transform::SetWorldPosY(float WPosY)
{
	if (parent)
		position.y = Vector3::Transform(Vector3(W._41, WPosY, W._43), parent->W.Invert()).y;
	else
		position.y = WPosY;
}

void Transform::SetWorldPosZ(float WPosZ)
{
	if (parent)
		position.z = Vector3::Transform(Vector3(W._41, W._42, WPosZ), parent->W.Invert()).z;
	else
		position.z = WPosZ;
}

void Transform::Setrotation(const Vector3 rotation)
{
	this->rotation =  rotation;
}

void Transform::SetangularVelocity(const Vector3 angularVelocity)
{
	this->angularVelocity =  angularVelocity;
}

void Transform::SetVelocity(const Vector3 velocity)
{
	this->velocity = velocity;
}

void Transform::MoveWorldPos(const Vector3& WScaleVec)
{
	if (parent)
		position += Vector3::TransformNormal(WScaleVec, parent->W.Invert());
	else
		position += WScaleVec;
}

Vector3 Transform::GetLocalPos()
{
	if (parent)
		return Vector3::Transform(position, parent->S);
	else
		return position;
}

void Transform::SetLocalPos(Vector3 WPos)
{
	if (parent)
		position = Vector3::Transform(WPos, parent->S.Invert());
	else
		position = WPos;
}

void Transform::SetLocalPosX(float WPosX)
{
	if (parent)
		position.x = WPosX / parent->S._11;
	else
		position.x = WPosX;
}

void Transform::SetLocalPosY(float WPosY)
{
	if (parent)
		position.y = WPosY / parent->S._22;
	else
		position.y = WPosY;
}

void Transform::SetLocalPosZ(float WPosZ)
{
	if (parent)
		position.z = WPosZ / parent->S._33;
	else
		position.z = WPosZ;
}

void Transform::MoveLocalPos(const Vector3& WScaleVec)
{
	if (parent)
	{
		Matrix InverseS;
		InverseS._11 = 1.0f / parent->S._11;
		InverseS._22 = 1.0f / parent->S._22;
		InverseS._33 = 1.0f / parent->S._33;
		Vector3 LScaleVec = Vector3::Transform(WScaleVec, InverseS);
		position += LScaleVec;
	}
	else
		position += WScaleVec;
}

Matrix Transform::GetLocalInverse()
{
	Matrix s = Matrix::CreateScale(scale);
	Matrix r = Matrix::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z);
	Matrix t = Matrix::CreateTranslation(position);
	Matrix w = s * r * t;
	return w.Invert();
}

void Transform::integrate(float duration)
{
	/* 강체의 질량이 무한대라면 적분을 하지 않는다 */
	if (inverseMass == 0.0f)
		return;

	/* 가속도를 계산한다 */
	prevAcceleration = acceleration;
	prevAcceleration += force * inverseMass;

	/* 각가속도를 계산한다 */
	Vector3 angularAcceleration = position * torque;

	/* 속도 & 각속도를 업데이트한다 */
	velocity += prevAcceleration * duration;
	angularVelocity += angularAcceleration * duration;

	/* 드래그를 적용한다 */
	velocity *= powf(linearDamping, duration);
	//angularVelocity *= powf(angularDamping, duration);

	force = Vector3(0.0f, 0.0f, 0.0f);
	torque = Vector3(0.0f, 0.0f, 0.0f);

}
