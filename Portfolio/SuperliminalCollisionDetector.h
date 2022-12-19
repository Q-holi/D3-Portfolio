#pragma once
#include "SuperliminalObject.h"
#include "SuperliminalSimulator.h"
#include "Contact.h"
#include "PlaneCollider.h"
class SuperliminalCollisionDetector
{

private:
    float friction;
    float objectRestitution;
    float groundRestitution;

public:
    SuperliminalCollisionDetector()
        : friction(0.6f), objectRestitution(0.3f), groundRestitution(0.2f) {}

    /* 충돌을 검출하고 충돌 정보를 contacts 에 저장한다 */
    void detectCollision(
        std::vector<Contact*>& contacts,
        std::unordered_map<unsigned int, SuperliminalObject*>& bodies,
        PlaneCollider& groundCollider
    );

    bool sphereAndPlane(
        std::vector<Contact*>& contacts,
        SuperliminalObject& bodies,
        const PlaneCollider& groundCollider
    );
};

