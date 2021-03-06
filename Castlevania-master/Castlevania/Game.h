﻿#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include"PlayScene.h"
#include"Textures.h"
#include"Animations.h"
#include"SimonProperties.h"

#define KEYBOARD_BUFFER_SIZE 1024


#define FONT_PATH L"GameContent\\Data\\prstart.ttf"

/*
Abstract class to define keyboard event handlers
*/
class CKeyEventHandler
{
public:
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

typedef CKeyEventHandler * LPKEYEVENTHANDLER;

class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	ID3DXFont* font;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	unordered_map<int, Scene*> scenes;
	int current_scene = 0;

	SimonProperties* player = new SimonProperties();
public:
	void InitKeyboard(LPKEYEVENTHANDLER handler);
	void Init(HWND hWnd);
	void Draw(int nx, float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);

	void DrawUI(bool followCam, int nx, float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);

	//lấy ra toạ độ cam
	D3DXVECTOR2 GetCamera() { return D3DXVECTOR2(cam_x, cam_y); }

	void GetCameraUI(float& x, float& y)
	{ 
		x = this->cam_x;
		y = this->cam_y;
	}
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	ID3DXFont* GetFont() {
		return this->font;
	}

	Scene* GetCurrentScene() { return scenes[current_scene]; }
	void SwitchScene(int scene_id);


	/// ta thao tác update loadresouce, render thông qua lớp game

	// load toàn bộ scene lưu vào scenestagemachine
	void Load();
	void Update(DWORD deltaTime);
	void Render();


	 // vẫn chạy thông qua class game debug để xem luồng rõ hơn
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void KeyState(BYTE* states);

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st, 
		float sr, 
		float sb,
		float &t, 
		float &nx, 
		float &ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }

	static CGame * GetInstance();

	~CGame();

	void SetSimonProp(SimonProperties* prop)
	{
		this->player = prop;
	}

	SimonProperties* GetSimonProp()
	{
		return this->player;
	}

	void DrawUIText(std::string text, RECT bound, bool followCam=false);

};


