#pragma once
#include"Scene.h"
#include"Simon.h"
#include"Map.h"
#include<queue>
class PlayScene:public Scene
{
    RECT cameraBoder;
    CSIMON* SIMON;
    vector<LPGAMEOBJECT> objects;
    Map* gameMap;
    void LoadSprite(const std::string& filePath, const int tex);
    void LoadAnimation(const string& filePath);

    std::queue<LPGAMEOBJECT> qObjects;

public:
    PlayScene(int id, std::string filepath,int TexId):Scene(id,filepath,TexId) {}
    D3DXVECTOR2 GetCamera();
    void SpawnObject(LPGAMEOBJECT obj) { this->qObjects.push(obj); }
    void Load() override;
    void UnLoad() override;
    
    void Update(DWORD deltaTime) override;
    void Render() override;

     void OnKeyDown(int KeyCode) override;
     void OnKeyUp(int KeyCode) override;
     void KeyState(BYTE* states) override;
    
};

