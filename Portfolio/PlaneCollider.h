#pragma once
class PlaneCollider
{
    //friend class CollisionDetector;

protected:
    /* ����� ����.
        ũ��� �׻� 1 �̴� */


    /* ���� �������� �������κ��� �󸶳� �־��� �ִ��� �����Ѵ� */


public:
    Vector3 normal;
    float offset;
    PlaneCollider(Vector3 normal, float offset);
};

