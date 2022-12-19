#pragma once
struct Contact
{
    SuperliminalObject* bodies[2]; //--�浹�ϴ� ��ü���� ������ (��ü-���� �浹 �� �迭�� �� ��° ���Ҵ� nullptr)
    Vector3 normal;//--�浹 ���� ����
    Vector3* contactPoint[2];//--�浹�� �Ͼ ������ ��ǥ
    float penetration;//--�� ������Ʈ�� ��ģ ����
    float restitution;//--�ݹ� ����� ���� ���
    float friction;
    /* ���� ��ݷ� (�浹 �ؼ� �� ���) */
    float normalImpulseSum;
    float tangentImpulseSum1;
    float tangentImpulseSum2;
};