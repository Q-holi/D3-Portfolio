#pragma once


class Application
{
	friend class Direct3D11;
	friend class Window;
	friend class Gui;
	friend class Input;
private:
	float		x, y;
	float		width;
	float		height;
	HINSTANCE	instance;
	HWND		handle;
	wstring		appName;
	bool		fullScreen;
public:
	bool		vSync;
	Color		background;
	int			fixFrame;
	float		deltaScale;
	float		soundScale;
public:
	Application() :instance(nullptr), handle(nullptr), vSync(false), fullScreen(false)
		, appName(L" "), width(1280.0f), height(720.0f), background(Color(0.7f, 0.7f, 0.7f, 1.0f))
		, fixFrame(400), deltaScale(1.0f), soundScale(1.0f),x(0.0f),y(0.0f) {}
	float	GetWidth() { return width; }
	float	GetX() { return x; }
	float	GetY() { return y; }
	float	GetHeight() { return height; }
	float	GetHalfWidth() { return width / 2.0f; }
	float	GetHalfHeight() { return height / 2.0f; }
	void	SetInstance(HINSTANCE instance)
	{ 
		if(!this->instance)
		this->instance = instance;
	}
	void	SetAppName(wstring appName) 
	{ 
		if (this->appName == L" ")
		this->appName = appName; 
	}
	//해상도변경은 D3D의 리사이즈 함수 이용!
};

template <typename T>
class Singleton
{
	//static
private:
	static T* instance;
public:
	static T* GetInstance()
	{
		if (!instance)
			instance = new T;

		return instance;
	};
	//member
public:
	virtual ~Singleton() {};
	void DeleteSingleton()
	{
		delete instance;
		instance = nullptr;
	};
};
template <typename T>
T* Singleton<T>::instance = nullptr;

//씬타입으로는 객체를만들수 없다.

enum class SceneState
{
	NONE,
	FADEIN,
	FADEOUT
};
class Scene
{
public:
	SceneState	state = SceneState::NONE;
	float		time;
	virtual ~Scene() {};
	//초기화
	virtual void Init() = 0;
	//해제
	virtual void Release() = 0;
	//Loop
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	//Window Resize
	virtual void ResizeScreen() = 0;
};


struct Int2
{
	int x;
	int y;
	Int2()
	{
		x = 0;
		y = 0;
	}
	Int2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator ==(Int2 dest)
	{
		return (x == dest.x && y == dest.y);
	}
	bool operator !=(Int2 dest)
	{
		return (x != dest.x || y != dest.y);
		//return !(*this == dest);
	}
};
