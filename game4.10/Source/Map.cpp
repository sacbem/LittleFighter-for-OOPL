#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Map.h"
#define Forest 100
#define MapWidth 3200* 0.75
#define BoundaryMin 
constexpr auto forestSky_dx = MapWidth / 800 * 0.75;
constexpr auto forestMountain_dx1 = MapWidth / 1100 * 0.75;
constexpr auto forestMountain_dx2 = MapWidth / 1400 * 0.75;
constexpr auto forestTree_dx = MapWidth / 2900 * 0.75;
constexpr auto forestLand_dx1 = MapWidth / 2950 * 0.75;
constexpr auto forestLand_dx2 = MapWidth / 3070 * 0.75;
constexpr auto forestLand_dx3 = MapWidth / 3200 * 0.75;
namespace game_framework {
    Map::Map(int mapID) {
        for (int i = 0; i < 4; i++) {
            mapBordary.push_back(true);
        }
        for (int i = 0; i < 4; i++) {
            characterInBorder.push_back(false);
        }
        map.reserve(30);
        InitializeAllObjs(mapID);
    }
    void Map::InitializeAllObjs(int mapID) {
        ////初始遊戲鏡頭位置
        gameScenesPos_X = gameScenesPos_Y = 0;
        //// 初始化地圖內容
        for (auto& i : map) {
            for (int o = 0; o < 10; o++) {
                i.push_back(0);
            }
        }
        switch (mapID) {
        case Forest:

            for (int floorNum = 0; floorNum < 3; floorNum++) {
                floors.push_back(new GameObject("Scenes", floorNum));
            }
            for (int weedNum = 0; weedNum < 3; weedNum++) {
                floorObjs.push_back(new GameObject("Scenes", weedNum));
            }
            for (int treeNum = 0; treeNum < 8; treeNum++) {
                backgroundFrontObjs.push_back(new GameObject("Scenes", treeNum));
            }
            for (int mountainNum = 0; mountainNum < 1; mountainNum++) {
                backgroundBackObjs.push_back(new GameObject("Scenes", mountainNum));
            }
            for (int skyNum = 0; skyNum < 3; skyNum++) {
                backgroundSkyObjs.push_back(new GameObject("Scenes", skyNum));
            }
            //for (int skyNum = 0; skyNum < 1; skyNum++) {
            //    backgroundSkyObjs.push_back(new GameObject("Scenes"));
            //}
            break;
        default:
            break;
        }
    }
    void Map::Load(int mapID) {
        int cnt = 0;
        switch (mapID) {
        case Forest:
            for (int i = 0; i < floorObjs.size() - 1;i++) {
                floorObjs[i]->Load(BITMAP_FOREST_L1 + i);
            }
            floorObjs[2]->Load(BITMAP_FOREST_L4);
            for (auto& tree : backgroundFrontObjs) {
                tree->Load(BITMAP_FOREST_T1, RGB(0, 0, 0));
            }
            for (auto& floor : floors) {
                floor->Load(BITMAP_GREEN);    
            }
            for (auto& sky : backgroundSkyObjs) {
                sky->Load(BITMAP_FOREST_M5, RGB(0, 0, 0));
            }
            backgroundBackObjs[0]->Load(BITMAP_BACKSCENE_FOREST, RGB(0, 0, 0));
           
            break;
        default:
            break;
        }
        InitializeMap(mapID);
    }
    void Map::GenerateLand(int mapID) {
        switch (mapID){
        case Forest:
            floorObjs[0]->SetTopLeft(0, 356);
            floorObjs[1]->SetTopLeft(300, 385);
            floorObjs[2]->SetTopLeft(600, 420);
            break;
        default:
            break;
        }
    }
    void Map::InitializeMap(int mapID) {
        int cnt = 0;
        switch (mapID) {
            case Forest:
                // weeds
                GenerateLand(mapID);
                //trees
                for (auto& tree : backgroundFrontObjs) {
                    tree->SetTopLeft(-800 + 250 * cnt, 165);
                    cnt++;
                }
                cnt = 0;
                //floors
                for (auto& floor : floors) {
                    floor->SetTopLeft(-1600 + 800 * cnt, 280);
                    cnt++;
                }
                cnt = 0;
                //sky
                for (auto& sky : backgroundSkyObjs) {
                    sky->SetTopLeft(-800 + 800 * cnt, 80);
                    cnt++;
                }
                ////mountains
                backgroundBackObjs[0]->SetTopLeft(-800, 100);
                break;
        }

    }
    void Map::StopDynamic() {  
        if (backgroundSkyObjs[0]->GetPositionXY("X") == 0 || backgroundSkyObjs[backgroundSkyObjs.size()-1]->GetPositionXY("X") == -800) {
            mapBordary[0] = false;
        }
        if (backgroundFrontObjs[0]->GetPositionXY("X") == 0 || backgroundFrontObjs[backgroundFrontObjs.size()-1]->GetPositionXY("X") == -800) {
            mapBordary[1] = false;
        }
        if (backgroundSkyObjs[0]->GetPositionXY("X") == 0 || backgroundSkyObjs[backgroundSkyObjs.size()-1]->GetPositionXY("X") == -800) {
            mapBordary[2] = false;
        }
        if (backgroundBackObjs[0]->GetPositionXY("X") == 0 || backgroundBackObjs[backgroundBackObjs.size() - 1]->GetPositionXY("X") == -1600) {
            mapBordary[3] = false;
        }
    }
    boolean Map::ResetCharactAccumulator(int distance1, int distance2) {
        if (distance1 > forestSky_dx || distance2 > forestSky_dx) {
            return true;
        }
        else {
            return false;
        }
    }
    void Map::DynamicScence(boolean IsLeft,int walkedDistance) {
        StopDynamic();
        int direction = IsLeft ? 1 : -1; // 往右 : 1 往左 : -1 
        if (mapBordary[0]) {
            if (walkedDistance > forestSky_dx) {
                for (auto& i : backgroundSkyObjs) {
                    i->SetTopLeft(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"));
                }
            }
        }
        if (mapBordary[1]) {
            if (walkedDistance > forestTree_dx) {
                for (auto& i : backgroundFrontObjs) {
                    //TRACE("1---------Dir %d    %d\n", i->GetPositionXY("X"), i->GetPositionXY("Y"));
                    i->SetTopLeft(i->GetPositionXY("X") + 1 * direction, i->GetPositionXY("Y"));
                    //TRACE("2---------Dir %d    %d\n", i->GetPositionXY("X"), i->GetPositionXY("Y"));
                }
            }
        }
        if (mapBordary[2]) {
            if (walkedDistance > forestTree_dx) {
                floorObjs[0]->SetTopLeft(floorObjs[0]->GetPositionXY("X") + 1 * direction, floorObjs[0]->GetPositionXY("Y"));
            }
            if (walkedDistance > forestTree_dx) {
                floorObjs[1]->SetTopLeft(floorObjs[1]->GetPositionXY("X") + 1 * direction, floorObjs[1]->GetPositionXY("Y"));
            }
            if (walkedDistance > forestTree_dx) {
                floorObjs[2]->SetTopLeft(floorObjs[2]->GetPositionXY("X") + 1 * direction, floorObjs[2]->GetPositionXY("Y"));
            }
        }
        if (mapBordary[3]) {
            if (walkedDistance > forestMountain_dx2) {
                backgroundBackObjs[0]->SetTopLeft(backgroundBackObjs[0]->GetPositionXY("X") + 1 * direction, backgroundBackObjs[0]->GetPositionXY("Y"));
            }
         }      
    }

    void Map::ScenesCamera(boolean IsRunning, boolean IsLeft, int walkedDistance) {
        int direction = IsLeft  ?  1 : -1; // 往右 : 1 往左 : -1 
        if (IsLeft) {
            if (IsRunning) {    //往左跑
                gameScenesPos_X++;
            }
            else if (!IsRunning && walkedDistance > 20) { //往左走
                gameScenesPos_X++;
            }
        }
        else if (!IsLeft) {
            if (IsRunning) {  //往右跑
                gameScenesPos_X--;
            }
            else if (!IsRunning && walkedDistance > 20) { //往右走
                gameScenesPos_X--;
            }
        }

    }

    void Map::PrintMap() {
        for (auto & i : backgroundSkyObjs) {
            i->OnShow();
        }
        for (auto& i : backgroundBackObjs) {
            i->OnShow();
        }
        for (auto i : floors) {
            i->OnShow();
        }
        for (auto& i : backgroundFrontObjs) {
            i->OnShow();
        }

        for (auto i : floorObjs) {
            i->OnShow();
        }

    }
    Map::~Map() {
        for (auto& i : floors) {
            delete i;
        }
        for (auto& i : floorObjs) {
            delete i;
        }
        for (auto& i : backgroundFrontObjs) {
            delete i;
        }
        for (auto& i : backgroundSkyObjs) {
            delete i;
        }
        for (auto& i : backgroundBackObjs) {
            delete i;
        }
        //floors.clear();
    }
   
}
    /// <summary> friend int GetScenesPos(Map &map,const string type);
    /// GameObject :    場景上所有物件的類別(武器、布景、道具)
    /// </summary>
    /// <param name="type"></param>

