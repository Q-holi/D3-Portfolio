#include "stdafx.h"

SuperliminalSimulator::~SuperliminalSimulator()
{
    /* 충돌 정보 해제 */
  /*  for (auto& contact : contacts)
        delete contact;*/

}
void SuperliminalSimulator::addGameObject(unsigned int id, SuperliminalObject& gameObject)
{

    gameObject.inverseMass = 1.0f / 5.0f;
    gameObject.acceleration = Vector3(0.0f,-gravity, 0.0f);
    //bodies.insert()

        //--insert( {key, value} )
    bodies[id] = &gameObject;
    //cout << "bodies" << id << &bodies[id] << endl;
    //cout << "bodies" << id << bodies[id]->inverseMass << endl;
}
void SuperliminalSimulator::Simulate(float duration)
{
    /* 물체들을 적분한다 */
    for (auto& body : bodies)
    {
        body.second->integrate(duration);
    }
    /* 물체 간 충돌을 검출한다 */
    //detector.detectCollision(contacts, bodies, groundCollider);


    //resolver.resolveCollision(contacts, DELTA);
    bodies[0]->MoveWorldPos(bodies[0]->GetAcceleration()*DELTA );
    bodies[1]->MoveWorldPos(bodies[1]->GetAcceleration()*DELTA );
    //bodies[0]->MoveWorldPos(bodies[0]->GetAcceleration()* bodies[0]->GetVelocity() *DELTA);

    contacts.clear();
}
