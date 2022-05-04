#pragma once
#include "GameObject.h"
//#include "Character.h"
namespace game_framework{
    class Map {
        //friend 
    public:
        Map(int mapID);
        int GetScenesPos(const string type);
        void ScenesCamera(boolean IsRunning, boolean IsLeft, int walkedDistance);
        //int GetScenesPos(Map& map, const string type);
        void Load(int mapID);
        void GenerateLand(int mapID);
        void PrintMap();
        void DynamicScence(boolean IsLeft,int walkedDistance);
        boolean ResetCharactAccumulator(int distance1,int distance2);
        ~Map();
        
    private:
        void InitializeAllObjs(int mapID);
        void StopDynamic();
        void InitializeMap(int mapID);
        //int rubberBandAccumulator(boolean IsRunning, boolean InBorder);
        //boolean CharacterDetector(Character character);
        int gameScenesPos_X, gameScenesPos_Y;
        vector<vector<int>> map;  // 2400*600 80*60 per blank;  30 * 10
        vector<boolean>mapBordary;//1:sky 2:tree 3:land 4: mountain
        vector<boolean> characterInBorder;
        vector<GameObject*> floors, floorObjs, backgroundFrontObjs, backgroundBackObjs, backgroundSkyObjs;
        /// <summary>
        /// floors :　場景地面
        /// floorObjs: 場景地面上物件
        /// backgroundFrontObjs : 場景-前景
        /// backgroundBackObjs: 場景-後景
        /// backgroundSkyObjs:場景-天空
        /// </summary>
    };



}