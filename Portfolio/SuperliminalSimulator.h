#pragma once
#include "SuperliminalCollisionDetector.h"
#include "SuperliminalCollisionResolver.h"
#include "SuperliminalObject.h"
#include "PlaneCollider.h"
#include <vector>
#include <unordered_map>



class SuperliminalSimulator
{

public:
    typedef std::unordered_map<unsigned int,  SuperliminalObject*>  Bodies;
    typedef std::vector< Contact*> Contacts;
    PlaneCollider groundCollider;
private:

public:
    Bodies bodies;
    Contacts contacts;
    SuperliminalCollisionResolver resolver;
    SuperliminalCollisionDetector detector;

    float gravity; //--ม฿ทย

    SuperliminalSimulator() : groundCollider(Vector3(0.0f, 1.0f, 0.0f), 0.0f), gravity(9.8f) {}
    ~SuperliminalSimulator();

    void addGameObject(unsigned int id, SuperliminalObject& gameObject);
    void Simulate(float duration = DELTA);
};