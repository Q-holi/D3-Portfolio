#pragma once
class SuperliminalCollisionResolver
{
private:
    int iterationLimit;
    float penetrationTolerance;
    float closingSpeedTolerance;

public:
    SuperliminalCollisionResolver()
        : iterationLimit(30), penetrationTolerance(0.0005f), closingSpeedTolerance(0.005f) {}

    void resolveCollision(std::vector<Contact*>& contacts, float deltaTime);

private:
    void sequentialImpulse(Contact* contact, float deltaTime);
};

