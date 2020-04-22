#pragma once
#include<Windows.h>
#include<string>
///
///abtrack class dùng để kế thừa
class Scene
{
protected:
	std::string FilePath;
	int id;
	int TexID;
	int MapID;
public:
	Scene(int id, std::string FilePath,int TexId)
	{
		this->FilePath = FilePath;
		this->id = id;
		this->TexID = TexId;
	}
	//dùng thay thế cho controctor mấy lớp kế  thừa
	virtual void Load() = 0;
	//dùng thay thế cho distractor mấy lớp kế  thừa
	virtual void UnLoad() = 0;


	virtual void Update(DWORD deltaTime) = 0;
	virtual void Render() = 0;

	//dùng để bắt phím của từng scene k bắt từ hàm main
	virtual void OnKeyDown(int KeyCode) {};
	virtual void OnKeyUp(int KeyCode) {};
	virtual void  KeyState(BYTE* states) {};
};

