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

    //*****************���������� �ʿ��� �� ������ **********************
    /* ������ ����.
    ���нĿ� Ȱ���ϱ� ����,
    ���Ѵ��� ����(ex. ���)�� ǥ���ϱ� ���ϴ� */
    float inverseMass;
    /* ��ü�� �ٶ󺸴� ���� */
    //GetForworad�� ����غ��� 
    /* ��ü�� �ӵ� */
    Vector3 velocity;

    /* ��ü�� ���ӵ� */
    Vector3 angularVelocity;

    /* ��ü�� ���ӵ�.
    ���� �߷� ���ӵ����� �����Ѵ� */
    Vector3 acceleration;



    /* ���� �����ӿ��� ��ü�� ���ӵ�.
    �߷� ���ӵ� + �ܺ� ���� ���� ���ӵ��� �����Ѵ� */
    Vector3 prevAcceleration;
    /* ���ӵ� ���� */
    float linearDamping;

    /* ���ӵ� ���� */
    float angularDamping;


    /* ��ü�� ������ �� & ��ũ */
    Vector3 force;
    Vector3 torque;
    //*****************���������� �ʿ��� �� ������ **********************

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

    //���� ���� ��ǥ
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

    //���� ������ ���� ��ǥ
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

