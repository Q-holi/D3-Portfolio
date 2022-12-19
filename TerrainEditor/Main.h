#pragma once


class Main : public Scene
{
private:
	Camera* Cam;
	Actor* Grid;

	Terrain* Map;
	Actor* Sphere;
	deque<Vector3> Way;

	float MoveValue;
	Vector3 P1, P2;
	float Dis;

	//상수버퍼에 갱신
	struct Brush
	{
		Vector3 point;
		float	range = 2.0f;

		float	shape;
		float	type;
		Vector2 padding;
	} brush;
	ID3D11Buffer* brushBuffer;

	//에디터에서만 존재하는 변수
	float	brushMaxHeight = 1000.0f;
	float	brushAddHeightScalr = 10.0f;
	int		brushTexture = 0;
	int		nodeEdit = 0;
	int     prevPick = -1;
public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void EditTerrain(Vector3 Pos);
};