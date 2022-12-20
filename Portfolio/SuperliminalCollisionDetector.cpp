#include "stdafx.h"
#include "SuperliminalObject.h"
#include "SuperliminalSimulator.h"
#include "PlaneCollider.h"
#include "Contact.h"

void SuperliminalCollisionDetector::detectCollision(std::vector<Contact*>& contacts, 
	std::unordered_map<unsigned int, SuperliminalObject*>& bodies, 
	const PlaneCollider& groundCollider)
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
	//--평면의 법선에 대한 구와 평면의 거리를 구한다 
	float distance = groundCollider.normal.Dot(bodies.position);
	distance -= groundCollider.offset;
	//--오브젝트가 Change상태면 충돌 감지를 무시 한다.
	if (bodies.state != SuperliminalObjectState::CHANGE) {
		//--구의 크기와 평면 거리를 구한 값보다 작으면 충돌을 감지한다.
		if (distance < bodies.scale.x)
		{
			Contact* newContact = new Contact;
			newContact->bodies[0] = &bodies;
			//--[1]이 nullptr이면 지면과의 충돌로 인지한다.
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
			//--성공적으로 감지하고 충돌 컨테이너의 값을 추가하면 true 반환
			return true;
		}
	}
	return false;
}
