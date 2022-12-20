#include "stdafx.h"
GameScene::GameScene()
{
	sky = Sky::Create();
	RenderUiArray.push_back(sky);

	Cam = Camera::Create();
	
	RenderUiArray.push_back(Cam);

	MainCamera = Camera::Create();


	user = new Player();

	Map = Terrain::Create();
	Map->LoadFile("PortfolioMap.xml");
	Map->CreateStructuredBuffer();
	Map->material->shadow = 1.0f;
	//Player->Find("Vampire")->material->shadow = 1.0f;
	//Player->Find("VampireMeshObject")->material->shadow = 1.0f;

	for (int i = 0; i < 4; i++) {
		wallArray[i] = Actor::Create();
		string str = "Wall_" + to_string(i + 1) + ".xml";
		wallArray[i]->LoadFile(str);
		RenderUiArray.push_back(wallArray[i]);
	}

	//cube1 = Actor::Create();
   // cube1->LoadFile("Sphere2.xml");
	//wall_1 = Actor::Create();
	//wall_1->LoadFile("Wall_1.xml");

	//wall_2 = Actor::Create();
	//wall_2->LoadFile("Wall_2.xml");

	//wall_3 = Actor::Create();
	//wall_3->LoadFile("Wall_3.xml");

	//wall_4 = Actor::Create();
	//wall_4->LoadFile("Wall_4.xml");

	for (int i = 0; i < 2; i++) {
		objectArray[i] = new SuperliminalObject();
	}
	objectArray[1]->LoadFile("testCube.xml");

	//sphere = new SuperliminalObject();

	//cubeBox = new SuperliminalObject();
	//cubeBox->LoadFile("testCube.xml");

	//sphere = Actor::Create();
	//sphere->LoadFile("testSphere.xml");



	shadow = new Shadow();

	testAim = UI::Create();
	testAim->LoadFile("AimTarget.xml");
	// cubeMap1 = new Environment(512, 512);
	 //cubeMap2 = new Environment(512, 512);
	 //cubeMap1->desc2.CubeMapType = 0;
	 //cubeMap2->desc2.CubeMapType = 2;
	postEffect = new PostEffect();
	gameRenderScene = new PostEffect();
	target = nullptr;

	bluePotal = Actor::Create();
	bluePotal->LoadFile("testPotal.xml");

	bluePotalMap = new Environment(512, 512);
	bluePotalMap->desc2.CubeMapType = 0;

	newObjectID = 0;


	simulator.addGameObject(newObjectID, *objectArray[0]);
	newObjectID++;
	simulator.addGameObject(newObjectID, *objectArray[1]);
	//for (int i = 0; i < 2; i++) {
	//   // cout << "objectArray" << i << &objectArray[i] << endl;
	//    newObjectID = i + 1;
	//    simulator.addGameObject(newObjectID, *objectArray[i]);

	//    cout << objectArray[i]->inverseMass << endl;
	//}
	ImGuiEditer = true;
	openHierarchy = false;

}

GameScene::~GameScene()
{
	Map->Release();
}

void GameScene::Init()
{

	time = 0.0f;
	Cam = (Camera*)user->Find("Camera");
	//Cam->LoadFile("Cam.xml");
	//Camera::main = Cam;
	//Camera::main = MainCamera;
	ResizeScreen();


}

void GameScene::Release()
{

}


void GameScene::Update()
{
#pragma region Debugging tool
	{
		
		ImGui::Begin("Debugging tool");                          // Create a window called "Hello, world!" and append into it.
		ImGui::Text("This is Test SuperliminalEditer Debugging tool.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("SuperliminalEditer", &ImGuiEditer);      // Edit bools storing our window open/close state

		ImGui::Text("Application average %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

		ImGuiStyle& style = ImGui::GetStyle();
		//style.GrabRounding = style.FrameRounding = 15.0f;
		static ImGuiStyle ref_saved_style;

		if (ImGui::ShowStyleSelector("Colors##Selector"))
			ref_saved_style = style;


		// Simplified Settings (expose floating-pointer border sizes as boolean representing 0.0f or 1.0f)
		if (ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 15.0f, "%.0f"))
			style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
		ImGui::End();
	}
	// Demonstrate the various window flags. Typically you would just use the default!
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool unsaved_document = false;

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
	if (no_close)           ImGuiEditer = NULL; // Don't pass our bool* to Begin

		// We specify a default position/size in case there's no data in the .ini file.
	// We only do it to make the demo applications a little more welcoming, but typically this isn't required.
	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	ImGui::Begin("SuperliminalEditer", &ImGuiEditer, window_flags);

	// Menu Bar
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
	if (ImGui::CollapsingHeader("Hierarchy") or openHierarchy)
	{
		sky->RenderHierarchy();
		user->RenderHierarchy();
		//Map->RenderHierarchy();
		//Cam->RenderHierarchy();
		//for (int i = 0; i < 4; i++) {
		//	wallArray[i]->RenderHierarchy();
		//}
		for (int i = 0; i < 2; i++) {
			objectArray[i]->RenderHierarchy();
		}
		testAim->RenderHierarchy();
		bluePotal->RenderHierarchy();
	}
	if (ImGui::CollapsingHeader("GameScene"))
	{
		ImVec2 size(400, 400);
		ImGui::Image((void*)postEffect->GetSRV(), size);
	}
	ImGui::End();
#pragma endregion

	//if (ImGuiEditer)
	//	Editer::ShowEditer(&ImGuiEditer, RenderUiArray);

	Camera::ControlMainCam();
	LIGHT->RenderDetail();
	shadow->RenderDetail();
	postEffect->RenderDetail();

	//ImGui::Begin("Hierarchy");
	//sky->RenderHierarchy();
	//user->RenderHierarchy();
	//Map->RenderHierarchy();
	//Cam->RenderHierarchy();
	////cube1->RenderHierarchy();
	//for (int i = 0; i < 4; i++) {
	//	wallArray[i]->RenderHierarchy();
	//}
	////wall_1->RenderHierarchy();
	////wall_2->RenderHierarchy();
	////wall_3->RenderHierarchy();
	////wall_4->RenderHierarchy();
	//for (int i = 0; i < 2; i++) {
	//	objectArray[i]->RenderHierarchy();
	//}
	////sphere->RenderHierarchy();
	////cubeBox->RenderHierarchy();
	//testAim->RenderHierarchy();
	//bluePotal->RenderHierarchy();
	//ImGui::End();

	if (INPUT->moveCk) {
		user->rotation.y += INPUT->movePosition.x * 0.001f;
		Cam->rotation.x += INPUT->movePosition.y * 0.001f;
	}



	simulator.Simulate(DELTA);
	for (int i = 0; i < 2; i++) {
		objectArray[i]->UpdatePhysics();
		if ((objectArray[i]->GetWorldPos().y - objectArray[i]->scale.x) < 0.1f)
			objectArray[i]->SetWorldPosY(0.0f + objectArray[i]->scale.x);

	}


	Util::Saturate(Cam->rotation.x, PI_DIV4 * -1, PI_DIV4);

	user->Update();
	Cam->Update();
	MainCamera->Update();

	Map->Update();
	sky->Update();
	testAim->Update();
	//cube1->Update();
	for (int i = 0; i < 4; i++) {
		wallArray[i]->Update();
	}

	//wall_1->Update();
	//wall_2->Update();
	//wall_3->Update();
	//wall_4->Update();
	HandleInput();
	ResizeTarget();

	//sphere->UpdatePhysics();
	//cubeBox->Update();
	bluePotal->Update();

}

void GameScene::LateUpdate()
{

	Ray Top;
	Top.position = user->GetWorldPos() + Vector3(0, 1000, 0);
	Top.direction = Vector3(0, -1, 0);
	Vector3 Hit2;
	if (Util::RayIntersectMap(Top, Map, Hit2))
	{
		user->SetWorldPos(Hit2);
	}
	//float x = App.GetX() + App.GetHalfWidth();
	//float y = App.GetY() + App.GetHalfHeight();
	//SetCursorPos(x, y);

	//Ray TopRay = Util::MouseToRay(INPUT->position, Camera::main);
	//Ray TopRay;
	//TopRay.direction = Vector3(0, -1, 0);
	//TopRay.position = user->GetWorldPos() + Vector3(0, 0.05f, 0);
	//Vector3 Hit;
	//if (Map->ComPutePicking(TopRay, Hit))
	//{
	//    user->SetWorldPos(Hit);
	//    cout << endl;
	//}

	//float x = App.GetX() + App.GetHalfWidth();
	//float y = App.GetY() + App.GetHalfHeight();

	//SetCursorPos(x, y);

}

void GameScene::PreRender()
{
	LIGHT->Set();
	//환경 매핑 그리기
	{
		Vector3 Dir = bluePotal->GetWorldPos() - user->GetWorldPos();
		float Distance = Dir.Length();
		Dir.Normalize();
		Vector3 reflect = Vector3::Reflect(Dir, bluePotal->GetUp());
		bluePotalMap->SetCapture(bluePotal->GetWorldPos() - reflect * Distance);
		sky->CubeMapRender();
		user->CubeMapRender();
		Map->CubeMapRender();
		for (int i = 0; i < 4; i++) {
			wallArray[i]->CubeMapRender();
		}
	}
	//환경 매핑 그리기
	{
		//cubeMap2->SetCapture(Camera::main->GetWorldPos());
		//sky->CubeMapRender();
	   // Player->CubeMapRender();
		//Map->CubeMapRender();
	}
	//그림자 텍스쳐 그리기
	{
		shadow->SetCapture(Vector3(0, 0, 0));
		Map->ShadowMapRender();
		user->ShadowMapRender();

	}
	//포스트이펙트 텍스쳐에 그리기
	{
		postEffect->SetCapture();
		Cam->Set();
		sky->Render();

		for (int i = 0; i < 4; i++) {
			wallArray[i]->Render();
		}

		for (int i = 0; i < 2; i++) {
			objectArray[i]->Render();
		}
		testAim->Render();

		shadow->SetTexture();
		Map->Render();
		user->Render();

	} 
	//포스트이펙트 텍스쳐에 그리기
	{
		gameRenderScene->SetCapture();
		MainCamera->Set();
		sky->Render();

		for (int i = 0; i < 4; i++) {
			wallArray[i]->Render();
		}

		for (int i = 0; i < 2; i++) {
			objectArray[i]->Render();
		}
		shadow->SetTexture();
		Map->Render();
		user->Render();

	}

}

void GameScene::Render()
{
	postEffect->Render();
	//gameRenderScene->Render();
}

void GameScene::ResizeScreen()
{
	Cam->width = App.GetWidth();
	Cam->height = App.GetHeight();
	Cam->viewport.width = App.GetWidth();
	Cam->viewport.height = App.GetHeight();
	MainCamera->width = App.GetWidth();
	MainCamera->height = App.GetHeight();
	MainCamera->viewport.width = App.GetWidth();
	MainCamera->viewport.height = App.GetHeight();

	if (postEffect)
	{
		postEffect->ResizeScreen(App.GetWidth(), App.GetHeight());
	}
	if (gameRenderScene)
	{
		gameRenderScene->ResizeScreen(App.GetWidth(), App.GetHeight());
	}
}

void GameScene::HandleInput()
{
	//-- 마우스 휠 버튼 클릭
	if (INPUT->KeyDown(VK_MBUTTON))
	{
		//--현재 target을 들고 있지 않으면
		if (target == nullptr)
		{
			//--현재 바라보고 있는 카메라 기준의 마우스 방향으로 Ray 생성
			Ray mouse = Util::MouseToRay(INPUT->position, Cam);
			Vector3 Hit2;

			for (int i = 0; i < ArraySize; i++) {
				if (Util::RayIntersectTri(mouse, objectArray[i], Hit2))
				{
					objectArray[i]->ObjectHandleIN();
					target = objectArray[i];
					objectArray[i]->selectHierarchy = true;
					openHierarchy = true;

					target->SetWorldPos(Hit2);

					Vector3 temp = Cam->GetWorldPos() - target->GetWorldPos();
					originalDistance = temp.Length();

					originalScale = target->scale.x;

					targetScale = target->scale;
				}
			}
		}
		//--들고 있던 targetObject 해제
		else
		{
			target->ObjectHandleOUT();
			target->selectHierarchy = false;
			openHierarchy = false;
			target = nullptr;
			
		}
	}
}

void GameScene::ResizeTarget()
{
	// If our target is null
	if (target == nullptr)
	{
		// Return from this method, nothing to do here
		return;
	}

	// Cast a ray forward from the camera position, ignore the layer that is used to acquire targets
	// so we don't hit the attached target with our ray
	//RaycastHit hit;
	//Ray hit;
	Ray mouse = Util::MouseToRay(INPUT->position, Cam);
	//mouse.position = Cam->GetWorldPos();
	//mouse.direction = Vector3(1000, 0, 0);
	Vector3 Hit2;
	for (int i = 0; i < 4; i++) {
		if (Util::RayIntersectTri(mouse, wallArray[i], Hit2))
			//if (Physics.Raycast(transform.position, transform.forward, out hit, Mathf.Infinity, ignoreTargetMask))
		{
			// Set the new position of the target by getting the hit point and moving it back a bit
			// depending on the scale and offset factor
			//target.position = hit.point - transform.forward * offsetFactor * targetScale.x;
			target->SetWorldPos(Hit2 - Cam->GetForward() * offsetFactor * targetScale * originalScale * 2.0f);



			// Calculate the current distance between the camera and the target object
			float currentDistance = (Cam->GetWorldPos() - target->GetWorldPos()).Length();

			// Calculate the ratio between the current distance and the original distance
			float s = currentDistance / originalDistance;

			// Set the scale Vector3 variable to be the ratio of the distances
			targetScale.x = targetScale.y = targetScale.z = s;

			// Set the scale for the target objectm, multiplied by the original scale
			target->scale = targetScale * originalScale;

		}
	}
}

void GameScene::HelpMarker(const char* desc)
{
	//ImGui::TextDisabled("(?)");
	//if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
	//{
	//	ImGui::BeginTooltip();
	//	ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
	//	ImGui::TextUnformatted(desc);
	//	ImGui::PopTextWrapPos();
	//	ImGui::EndTooltip();
	//}
}

