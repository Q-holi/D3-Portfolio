#pragma once
#define ArraySize 2
#include "SuperliminalObject.h"
#include "SuperliminalSimulator.h"
class GameScene : public Scene
{
private:
	Camera* Cam;

	Camera* MainCamera;

	Sky* sky;
	class Player* user;
	Terrain* Map;


	Actor* wallArray[4];

	//class SuperliminalObject* sphere;
	//class SuperliminalObject* cubeBox;
	//Actor* cubeBox;
	SuperliminalObject* objectArray[2];

	UI* testAim;
	Shadow* shadow;

	//Environment* cubeMap2;
	PostEffect* postEffect = nullptr;
	PostEffect* gameRenderScene = nullptr;

	SuperliminalObject* target; // The target object we picked up for scaling


	//LayerMask targetMask;        // The layer mask used to hit only potential targets with a raycast
	//LayerMask ignoreTargetMask;  // The layer mask used to ignore the player and target objects while raycasting
	float offsetFactor = 1.0f;          // The offset amount for positioning the object so it doesn't clip into walls

	float originalDistance;             // The original distance between the player camera and the target
	float originalScale;                // The original scale of the target objects prior to being resized
	Vector3 targetScale;                // The scale we want our object to be set to each frame

	Environment* bluePotalMap;
	Actor* bluePotal;

	vector<Actor*> RenderUiArray;


	unsigned int newObjectID;
	//--SuperliminalSimulator Start
	SuperliminalSimulator simulator;
	bool ImGuiEditer;
public:
	bool openHierarchy;

public:
	GameScene();
	~GameScene();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void HandleInput();
	void ResizeTarget();
	static void HelpMarker(const char* desc);
	
};

