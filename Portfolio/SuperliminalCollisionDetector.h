#pragma once
#include "SuperliminalObject.h"
#include "SuperliminalSimulator.h"
#include "Contact.h"
#include "PlaneCollider.h"
class SuperliminalCollisionDetector
{
    /*�浹�� �����Ǹ� �浹 ���� ����ü�� ���� �Ҵ��� ��
�����͸� �浹 ���� �����̳�(std::vector<Contact*>)�� push �Ѵ�.*/
private:
    float friction;//--����
    float objectRestitution;//--������Ʈ�� �ݹ� ���
    float groundRestitution;//--������ �ݹ� ���
    //--�ݹ� -> ��ü�� �浹 ���� �ӵ��� ������ ��Ÿ���� �м�
public:
    SuperliminalCollisionDetector()
        : friction(0.6f), objectRestitution(0.3f), groundRestitution(0.2f) {}

    /* �浹�� �����ϰ� �浹 ������ contacts �� �����Ѵ� */
    void detectCollision(
        std::vector<Contact*>& contacts,
        std::unordered_map<unsigned int, SuperliminalObject*>& bodies,
        const PlaneCollider& groundCollider
    );
    /*���� ������ �浹 �˻�*/
    bool sphereAndPlane(
        std::vector<Contact*>& contacts,
        SuperliminalObject& bodies,
        const PlaneCollider& groundCollider
    );
    //--���� �浹 ���� �߰� ���� 
    //--*******************************************************************************
};

