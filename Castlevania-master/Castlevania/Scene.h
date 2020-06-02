#pragma once
#include<Windows.h>
#include<string>
class Scene
{
protected:
	std::string FilePath;
	int id;
	int TexID;
	int MapID;
	std::string MapPath;
public:
	Scene(int id, std::string FilePath,int TexId,std::string Map)
	{
		this->FilePath = FilePath;
		this->id = id;
		this->TexID = TexId;
		this->MapPath = Map;
	}
	virtual void Load() = 0;
	virtual void UnLoad() = 0;


	virtual void Update(DWORD deltaTime) = 0;
	virtual void Render() = 0;

	virtual void OnKeyDown(int KeyCode) {};
	virtual void OnKeyUp(int KeyCode) {};
	virtual void  KeyState(BYTE* states) {};
};

