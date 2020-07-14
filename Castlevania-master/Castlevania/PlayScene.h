#pragma once
#include"Scene.h"
#include"Simon.h"
#include"Map.h"
#include<queue>
#include "SkeletonTrigger.h"
#include "SimonProperties.h"
#include "Hub.h"
#include "Grid.h"
class Hub;
class PlayScene:public Scene
{
    RECT cameraBoder;
    CSIMON* SIMON;
    Hub* hub;
    vector<LPGAMEOBJECT> objects;
    Map* gameMap;
    void LoadSprite(const std::string& filePath, const int tex);
    void LoadAnimation(const string& filePath);
    
    std::queue<LPGAMEOBJECT> qObjects;

    SimonProperties* simon_properties;

    unsigned int stateTime = 300;
    void GameTimeCounter();
    
    DWORD timeCounter_start = 0;

    RECT BossCamera;

    Grid* grid;
public:
    PlayScene(int id, std::string filepath,int TexId,std::string Map,int StageID):Scene(id,filepath,TexId,Map,StageID)
    {
        simon_properties = NULL;
    }
    D3DXVECTOR2 GetCamera();
    void SpawnObject(LPGAMEOBJECT obj) { this->qObjects.push(obj); }
    void Load() override;
    void UnLoad() override;
    
    void LoadDefault();
    void LoadSpriteDefault(const std::string& filePath, const int tex);
    void LoadAnimationDefault(const string& filePath);

    void Update(DWORD deltaTime) override;
    void Render() override;

     void OnKeyDown(int KeyCode) override;
     void OnKeyUp(int KeyCode) override;
     void KeyState(BYTE* states) override;
    
     CSIMON* GetSimon()
     {
         return this->SIMON;
     }

     unsigned int GetTime() {
         return this->stateTime;
     }

     int GetStageID()
     {
         return this->StageID;
     }

     RECT GetBossCamera()
     {
         return this->BossCamera;
     }

     Hub* GetHub()
     {
         return this->hub;
     }
};

