#include "framework.h"

Animation::Animation()
{
	frameMax = 0;
	boneMax = 0;
	tickPerSecond = 0;
	arrFrameBone = nullptr;
	file = "";
}

Animation::~Animation()
{
	for (UINT i = 0; i < frameMax; i++)
	{
		delete[] arrFrameBone[i];
	}
	delete[] arrFrameBone;
}


void Animation::LoadFile(string file)
{
	this->file = file;
	BinaryReader in;
	wstring path = L"../Contents/Animation/" + Util::ToWString(file);
	in.Open(path);

	frameMax = in.Int();
	boneMax = in.Int();
	tickPerSecond = in.Float();

	arrFrameBone = new Matrix * [frameMax];
	for (UINT i = 0; i < frameMax; i++)
	{
		arrFrameBone[i] = new Matrix[boneMax];
	}

	for (UINT i = 0; i < frameMax; i++)
	{
		for (UINT j = 0; j < boneMax; j++)
		{
			arrFrameBone[i][j] = in.matrix();
		}
	}
	in.Close();
}

void Animation::SaveFile(string file)
{
	this->file = file;
	BinaryWriter out;
	wstring path = L"../Contents/Animation/" + Util::ToWString(file);
	out.Open(path);

	out.Int(frameMax);
	out.Int(boneMax);
	out.Float(tickPerSecond);

	for (UINT i = 0; i < frameMax; i++)
	{
		for (UINT j = 0; j < boneMax; j++)
		{
			out.matrix(arrFrameBone[i][j]);
		}
	}
	out.Close();
}

void Animations::AnimatorUpdate(Animator& Animator)
{
	if (Animator.animState == AnimationState::LOOP)
	{
		Animator.frameWeight += DELTA * playList[Animator.animIdx]->tickPerSecond * aniScale;
		if (Animator.frameWeight >= 1.0f)
		{
			Animator.frameWeight = 0.0f;
			Animator.currentFrame++;
			Animator.nextFrame++;
			if (Animator.nextFrame >= playList[Animator.animIdx]->frameMax)
			{
				Animator.currentFrame = 0;
				Animator.nextFrame = 1;
			}
		}
	}
	else if (Animator.animState == AnimationState::ONCE)
	{
		Animator.frameWeight += DELTA * playList[Animator.animIdx]->tickPerSecond * aniScale;
		if (Animator.frameWeight >= 1.0f)
		{
			Animator.frameWeight = 0.0f;
			Animator.currentFrame++;
			Animator.nextFrame++;
			if (Animator.nextFrame >= playList[Animator.animIdx]->frameMax)
			{
				Animator.currentFrame--;
				Animator.nextFrame--;
				/*Animator.currentFrame = 0;
				Animator.nextFrame = 1;*/
				Animator.animState = AnimationState::STOP;
			}
		}
	}
}

Animations::Animations()
{
	isChanging = false;
}

Animations::~Animations()
{
	for (int i = 0; i < playList.size(); i++)
	{
		SafeReset(playList[i]);
	}
}

void Animations::Update()
{
	if (isChanging)
	{
		AnimatorUpdate(nextAnimator);
		Changedtime += DELTA;
		if (Changedtime > blendtime)
		{
			Changedtime = 0.0f;
			//다음애니메이션을 현재애니메이션으로 바꾼다.
			currentAnimator = nextAnimator;
			isChanging = false;
		}
	}
	AnimatorUpdate(currentAnimator);
}

Matrix Animations::GetFrameBone(int boneIndex)
{
	if (isChanging)
	{
		return
			playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.nextFrame][boneIndex]
			* (1.0f - Changedtime / blendtime)
			+
			(playList[nextAnimator.animIdx]->arrFrameBone[nextAnimator.nextFrame][boneIndex]
				* nextAnimator.frameWeight +
				playList[nextAnimator.animIdx]->arrFrameBone[nextAnimator.currentFrame][boneIndex]
				* (1.0f - nextAnimator.frameWeight)) * (Changedtime / blendtime);
	}

	return playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.nextFrame][boneIndex]
		* currentAnimator.frameWeight +
		playList[currentAnimator.animIdx]->arrFrameBone[currentAnimator.currentFrame][boneIndex]
		* (1.0f - currentAnimator.frameWeight);
}

void Animations::PlayAnimation(AnimationState state, UINT idx, float blendtime)
{
	Changedtime = 0.0f;

	isChanging = true;

	currentAnimator.animState = AnimationState::STOP;
	nextAnimator.animState = state;
	this->blendtime = blendtime;
	nextAnimator.animIdx = idx;
	nextAnimator.currentFrame = 0;
	nextAnimator.nextFrame = 1;
}

void Animations::RenderDetail()
{
	ImGui::Text("PlayTime : %f", GetPlayTime());
	ImGui::SliderFloat("AniScale", &aniScale, 0.001f, 10.0f);


	static int item_current = 0;

	std::vector<std::string> my_vec;

	for (int n = 0; n < playList.size(); n++)
	{
		my_vec.push_back(playList[n]->file);
	}
	
	int indexnumber = ImGuiComboUI("Animations List", my_vec[item_current], my_vec, item_current);
	item_current = indexnumber;
	
	ImGui::Separator();
	//-- 각 기능에 맞는 버튼을 생성한다.
	if (ImGui::Button("STOP"))
	{
		PlayAnimation(AnimationState::STOP, indexnumber);
	}
	ImGui::SameLine();
	if (ImGui::Button("ONCE"))
	{
		PlayAnimation(AnimationState::ONCE, indexnumber);
	}
	ImGui::SameLine();
	if (ImGui::Button("LOOP"))
	{
		PlayAnimation(AnimationState::LOOP, indexnumber);
	}
	//--Animation의 출력은 반환받은 Combo인덱스 번호를 사용하여 출력







	/*for (UINT i = 0; i < playList.size(); i++)
	{
		string name = to_string(i) + playList[i]->file;
		string button = name + "Stop";

		
		if (ImGui::Button(button.c_str()))
		{
			PlayAnimation(AnimationState::STOP, i);
		}
		ImGui::SameLine();
		button = name + "Once";
		if (ImGui::Button(button.c_str()))
		{
			PlayAnimation(AnimationState::ONCE, i);
		}
		ImGui::SameLine();
		button = name + "Loop";
		if (ImGui::Button(button.c_str()))
		{
			PlayAnimation(AnimationState::LOOP, i);
		}


	}*/
}

int Animations::ImGuiComboUI(const std::string& caption, std::string& current_item,  std::vector<std::string>& items,int item_current)
{
	//--ImGui.h에서 수정이 가능하지만 Read속성으로 불러와  Animations에서 수정
	//--!ImGui는 string으로 받을수 있는 타입이 없다.!
	static int  number = 0;
	//--current_item List클릭 후 보여질 Ainmation의 Name
	if (ImGui::BeginCombo(caption.c_str(), current_item.c_str())) {
		for (int n = 0; n < items.size(); n++) {
			bool is_selected = (current_item == items[n]);
			if (ImGui::Selectable(items[n].c_str(), is_selected)) {
				//--List중 선택 후 static number에 번호를 담고 리턴해준다.
				number = n;
			}
		}
		ImGui::EndCombo();
	}
	return number;
}

float Animations::GetPlayTime()
{
	if (isChanging)
	{
		return (float)nextAnimator.nextFrame /
			(float)(playList[nextAnimator.animIdx]->frameMax - 1);
	}
	return (float)currentAnimator.nextFrame /
		(float)(playList[currentAnimator.animIdx]->frameMax - 1);
}
