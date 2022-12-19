#pragma once
struct Contact
{
    SuperliminalObject* bodies[2]; //--충돌하는 강체들의 포인터 (강체-지면 충돌 시 배열의 두 번째 원소는 nullptr)
    Vector3 normal;//--충돌 법선 벡터
    Vector3* contactPoint[2];//--충돌이 일어난 지점의 좌표
    float penetration;//--두 오브젝트가 겹친 정도
    float restitution;//--반발 계수와 마찰 계수
    float friction;
    /* 누적 충격량 (충돌 해소 시 사용) */
    float normalImpulseSum;
    float tangentImpulseSum1;
    float tangentImpulseSum2;
};