#include "stdafx.h"
#include "SuperliminalObject.h"
#include "SuperliminalSimulator.h"
#include "PlaneCollider.h"
#include "Contact.h"

void SuperliminalCollisionDetector::detectCollision(std::vector<Contact*>& contacts, 
	std::unordered_map<unsigned int, SuperliminalObject*>& bodies, 
	PlaneCollider& groundCollider)
{
	for (auto i = bodies.begin(); i != bodies.end(); ++i)
	{
		SuperliminalObject* colliderPtrI = i->second;
		sphereAndPlane(contacts, *colliderPtrI, groundCollider);
	}


}

bool SuperliminalCollisionDetector::sphereAndPlane(std::vector<Contact*>& contacts, 
	SuperliminalObject& bodies, 
	const PlaneCollider& groundCollider)
{
	/* 평면의 법선에 대한 구와 평면의 거리를 구한다 */
	float distance = groundCollider.normal.Dot(bodies.position);
	distance -= groundCollider.offset;
	if (bodies.state != SuperliminalObjectState::CHANGE) {
		if (distance < bodies.scale.x)
		{
			cout << "지면과 충돌" << distance << endl;
			Contact* newContact = new Contact;
			newContact->bodies[0] = &bodies;
			newContact->bodies[1] = nullptr;
			newContact->normal = groundCollider.normal;
			newContact->contactPoint[0] = new Vector3(bodies.position - groundCollider.normal * distance);
			newContact->contactPoint[1] = nullptr;
			newContact->penetration = bodies.scale.x - distance;
			newContact->restitution = groundRestitution;
			newContact->friction = friction;
			newContact->normalImpulseSum = 0.0f;
			newContact->tangentImpulseSum1 = 0.0f;
			newContact->tangentImpulseSum2 = 0.0f;

			contacts.push_back(newContact);
			return true;

		}
	}
	return false;
}
