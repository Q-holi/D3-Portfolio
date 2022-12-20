#pragma once
#include "SuperliminalObject.h"
#include "SuperliminalSimulator.h"
#include "Contact.h"
#include "PlaneCollider.h"
class SuperliminalCollisionDetector
{
    /*충돌이 감지되면 충돌 정보 구조체를 동적 할당한 후
포인터를 충돌 정보 컨테이너(std::vector<Contact*>)에 push 한다.*/
private:
    float friction;//--마찰
    float objectRestitution;//--오브젝트의 반발 계수
    float groundRestitution;//--지면의 반발 계수
    //--반발 -> 물체의 충돌 전후 속도의 비율을 나타내는 분수
public:
    SuperliminalCollisionDetector()
        : friction(0.6f), objectRestitution(0.3f), groundRestitution(0.2f) {}

    /* 충돌을 검출하고 충돌 정보를 contacts 에 저장한다 */
    void detectCollision(
        std::vector<Contact*>& contacts,
        std::unordered_map<unsigned int, SuperliminalObject*>& bodies,
        const PlaneCollider& groundCollider
    );
    /*구와 지면의 충돌 검사*/
    bool sphereAndPlane(
        std::vector<Contact*>& contacts,
        SuperliminalObject& bodies,
        const PlaneCollider& groundCollider
    );
    //--여러 충돌 감지 추가 구현 
    //--*******************************************************************************
};

