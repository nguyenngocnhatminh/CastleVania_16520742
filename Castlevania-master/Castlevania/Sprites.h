#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class CSprite
{
	string id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;

	bool isDefault = false;

	LPDIRECT3DTEXTURE9 texture;
public: 
	CSprite(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha = 255,int nx=0);

	void DrawUI(int nx, float x, float y, int alpha = 255, bool followCam = true);

	void SetIsDefault(bool df)
	{
		this->isDefault = df;
	}

	bool GetIsDefault()
	{
		return this->isDefault;
	}
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<string, LPSPRITE> sprites;

public:
	void Add(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(string id);
	LPSPRITE &operator[](string id) {return sprites[id];}
	void Clear();
	static CSprites * GetInstance();

};
