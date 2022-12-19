#include "framework.h"

UI* UI::Create(string name)
{
	UI* temp = new UI();
	temp->name = name;
	temp->type = ObType::UI;

	temp->mesh = RESOURCE->meshes.Load("6.UI.mesh");
	temp->shader = RESOURCE->shaders.Load("6.Cube.hlsl");
	return temp;
}

void UI::Update()
{
	float left = GetWorldPos().x - S._11 * 0.5f;
	float right = GetWorldPos().x + S._11 * 0.5f;
	float top = GetWorldPos().y + S._22 * 0.5f;
	float bottom = GetWorldPos().y - S._22 * 0.5f;

	if (left < INPUT->NDCPosition.x and INPUT->NDCPosition.x < right
		and bottom < INPUT->NDCPosition.y and
		INPUT->NDCPosition.y < top)
	{
		//함수포인터가 할당 되었다면 실행
		if (mouseOver) mouseOver();

		if (INPUT->KeyDown(VK_LBUTTON))
		{
			Press = true;
			if (mouseDown) mouseDown();
		}

	}

	if (Press)
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			if (mousePress) mousePress();
		}
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			Press = false;

			if (mouseUp) mouseUp();
		}
	}

	Actor::Update();

	

	
	
}

bool UI::MouseOver()
{
	float left = GetWorldPos().x - S._11 * 0.5f;
	float right = GetWorldPos().x + S._11 * 0.5f;
	float top = GetWorldPos().y + S._22 * 0.5f;
	float bottom = GetWorldPos().y - S._22 * 0.5f;

	if (left < INPUT->NDCPosition.x and INPUT->NDCPosition.x < right
		and bottom < INPUT->NDCPosition.y and
		INPUT->NDCPosition.y < top)
	{
		return true;
	}
	return false;
}
