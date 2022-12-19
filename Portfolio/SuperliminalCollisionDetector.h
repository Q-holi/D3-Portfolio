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

    /* �浹�� �����ϰ� �浹 ������ contacts �� �����Ѵ� */
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

