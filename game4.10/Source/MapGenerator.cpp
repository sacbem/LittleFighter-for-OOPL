#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <typeinfo>
#include "MapGenerator.h"
namespace game_framework {
    MapGenerator::MapGenerator(){
        //CMovingBitmap *obj1, *obj2, *obj3, *obj4, *obj5, *obj6;
        //obj1 = new CMovingBitmap; obj2 = new CMovingBitmap; obj3 = new CMovingBitmap;
        //obj4 = new CMovingBitmap; obj5 = new CMovingBitmap; obj6 = new CMovingBitmap;
        //CMovingBitmap obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9, obj10, obj11, obj12;
       

        //landsPosXY.reserve(4);
        //wallPosXY.reserve(4);
        
    }
    void MapGenerator::Initialize(int) {
        weeds.push_back(weed1); weeds.push_back(weed2);
        weeds.push_back(weed3); weeds.push_back(weed4);
       
        //SetWallsPosition();
    }
    void MapGenerator::Load(int) {
        Initialize(0);
        int cnt = 0;
        backGreen.LoadBitmap(BITMAP_GREEN);
        for (auto &i : weeds) {
            i.LoadBitmap(BITMAP_FOREST_L1 + cnt);
            cnt++;
        }
        backGreen.SetTopLeft(0, 300);
        weeds[0].SetTopLeft(0, 300);
        weeds[1].SetTopLeft(210, 390);
        weeds[2].SetTopLeft(385, 374);
        weeds[3].SetTopLeft(170, 385);

        
    }
    void  MapGenerator::SetLandPosition() {

        //4 :206*106
        //3 :232*95
        //2 :225*89
        //1 :175*74
        //t :253*162
        int cnt = 0;
        for (auto &i : weeds) {
            i.SetTopLeft(landsPosXY[cnt][0], landsPosXY[cnt][1]);
            cnt++;
        }

    }
    void MapGenerator::SetWallPosition() {

    }
    void MapGenerator::PrintMap() {
        backGreen.ShowBitmap();
        for (auto i : weeds) {
            i.ShowBitmap();
        }
    }
    void MapGenerator::ScenesCamera(boolean ISLEFT,int type) {
        if (type == 0) {
            for (int x = 0; x < 4; x++) {
                if (ISLEFT) {
                    landsPosXY[x][0] -= 10;
                    if (landsPosXY[x][0] < 0) {
                        landsPosXY[x][0] = 750;
                    }
                }
                else {
                    landsPosXY[x][0] += 10;
                    if (landsPosXY[x][0] >= 800) {
                        landsPosXY[x][0] = 0;
                    }
                }
            }
        }
        else if (type == 1) {
            for (int x = 0; x < 50; x++) {
                for (int i = 0; i < 4; i++) {
                    if (ISLEFT) {
                        landsPosXY[i][0] -= 1;
                        if (landsPosXY[i][0] < 0) {
                            landsPosXY[i][0] = 750;
                        }
                    }
                    else {
                        landsPosXY[i][0] += 1;
                        if (landsPosXY[i][0] >= 800) {
                            landsPosXY[i][0] = 0;
                        }
                    }
                }
            }
        }

        SetLandPosition();
    }

    MapGenerator::~MapGenerator() {}
}

/*

//lands[0].SetTopLeft(0, 300);//1
//lands[1].SetTopLeft(0, 370);//2
//lands[2].SetTopLeft(0, 450 - 3);//1

//lands[3].SetTopLeft(0 + 170, 300);//3
//lands[4].SetTopLeft(0 + 210, 300 + 90);//1
//lands[5].SetTopLeft(0 + 170, 390 + 65 - 23);//2

//lands[6].SetTopLeft(170 + 220, 300);//1
//lands[7].SetTopLeft(205 + 170, 300 + 74);//1
//lands[8].SetTopLeft(165 + 220, 373 + 74);//1

//lands[9].SetTopLeft(170 + 220 + 170, 300);//1
//lands[10].SetTopLeft(205 + 170 + 170, 300 + 74 );//1
//lands[11].SetTopLeft(165 + 220 + 170, 373 + 74 );//1
*/