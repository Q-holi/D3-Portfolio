#pragma once
class PlaneCollider
{
    //friend class CollisionDetector;

protected:
    /* 평면의 법선.
        크기는 항상 1 이다 */


    /* 법선 방향으로 원점으로부터 얼마나 멀어져 있는지 저장한다 */


public:
    Vector3 normal;
    float offset;
    PlaneCollider(Vector3 normal, float offset);
};

