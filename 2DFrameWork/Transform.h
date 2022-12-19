#pragma once
class Transform
{
protected:
    static bool         worldPos;
    static ID3D11Buffer* WBuffer;
public:
    static void CreateStaticMember();
    static void DeleteStaticMember();
protected:

public:
    Vector3				position;
	Matrix				S, R, T, RT, W;
	Vector3				scale;
	Vector3				rotation;
    class GameObject*   parent;

    //*****************물리엔진에 필요한 각 변수들 **********************
    /* 질량의 역수.
    적분식에 활용하기 좋고,
    무한대의 질량(ex. 배경)을 표현하기 편하다 */
    float inverseMass;
    /* 강체가 바라보는 방향 */
    //GetForworad를 사용해보자 
    /* 강체의 속도 */
    Vector3 velocity;

    /* 강체의 각속도 */
    Vector3 angularVelocity;

    /* 강체의 가속도.
    보통 중력 가속도만을 저장한다 */
    Vector3 acceleration;



    /* 직전 프레임에서 강체의 가속도.
    중력 가속도 + 외부 힘에 의한 가속도를 저장한다 */
    Vector3 prevAcceleration;
    /* 선속도 댐핑 */
    float linearDamping;

    /* 각속도 댐핑 */
    float angularDamping;


    /* 강체에 가해진 힘 & 토크 */
    Vector3 force;
    Vector3 torque;
    //*****************물리엔진에 필요한 각 변수들 **********************

protected:
	void	SaveTransform(Xml::XMLElement* This, Xml::XMLDocument* doc);
	void	LoadTransform(Xml::XMLElement* This);
public:
	Transform();
	virtual ~Transform() {};
    virtual void	Update();
    void            UpdateAnim(Matrix&& bone);
    virtual void	RenderDetail();
    virtual void    Set();
  
public:
	Vector3 GetRight() { return Vector3(RT._11, RT._12, RT._13); }
	Vector3 GetUp() { return Vector3(RT._21, RT._22, RT._23); }
	Vector3 GetForward() { return Vector3(RT._31, RT._32, RT._33); }

    //월드 공간 좌표
    // Read
    Vector3     GetWorldPos();
    // = Write
    void        SetWorldPos(Vector3 WPos);
    void        SetWorldPosX(float WPosX);
    void        SetWorldPosY(float WPosY);
    void        SetWorldPosZ(float WPosZ);
    void        Setrotation(const Vector3 rotation);
    void        SetangularVelocity(const Vector3 angularVelocity);
    void        SetVelocity(const Vector3 velocity);
    // +=
    void        MoveWorldPos(const Vector3& WScaleVec);

    //월드 스케일 로컬 좌표
    Vector3     GetLocalPos();
    void        SetLocalPos(Vector3 WPos);
    void        SetLocalPosX(float WPosX);
    void        SetLocalPosY(float WPosY);
    void        SetLocalPosZ(float WPosZ);
    void        MoveLocalPos(const Vector3& WScaleVec);
    Matrix      GetLocalInverse();

    void integrate(float duration);
    float GetInverseMass() const {return inverseMass;};
    Vector3 GetVelocity() const { return velocity;};
    Vector3 GetAcceleration() const { return acceleration;};
    Vector3 GetAngularVelocity() const { 
        //rotation = angularVelocity;
        return angularVelocity; };
};

